
#include <stdlib.h>
#include "ml4f.h"
#include "mlrunner.h"

// Pointer to the model in flash
static uint32_t* MODEL_ADDRESS = NULL;

/*****************************************************************************/
/* Private API                                                               */
/*****************************************************************************/
/**
 * @return True if the model header is valid, False otherwise.
 */
static bool is_model_valid(void* model_address) {
    ml_model_header_t *model_header = (ml_model_header_t *)model_address;
    if (model_header->magic0 != MODEL_HEADER_MAGIC0) {
        return false;
    }
    // We should have at least one label, and samples period, length and dimensions
    if (
        model_header->number_of_labels == 0 ||
        model_header->samples_period == 0 ||
        model_header->samples_length == 0 ||
        model_header->sample_dimensions == 0
    ) {
        return false;
    }
    // Also check the ML4F header magic values to ensure it's there too
    ml4f_header_t *ml4f_model = (ml4f_header_t *)((uint32_t)model_header + model_header->model_offset);
    if (ml4f_model->magic0 != ML4F_MAGIC0 || ml4f_model->magic1 != ML4F_MAGIC1) {
        return false;
    }
    return true;
}

/**
 * @brief Get a pointer to the ML4F model.
 *
 * @return The ML4F model or NULL if the model is not present or invalid.
 */
static ml4f_header_t* get_ml4f_model() {
    if (MODEL_ADDRESS == NULL || !is_model_valid(MODEL_ADDRESS)) {
        return NULL;
    }
    ml_model_header_t *model_header = (ml_model_header_t *)MODEL_ADDRESS;
    return (ml4f_header_t *)((uint32_t)model_header + model_header->model_offset);
}

/*****************************************************************************/
/* Public API                                                                */
/*****************************************************************************/
bool ml_setModel(void *model_address) {
    // Check if the model is valid
    if (!is_model_valid(model_address)) {
        return false;
    }
    MODEL_ADDRESS = (uint32_t *)model_address;
    return true;
}

bool ml_isModelPresent() {
    return MODEL_ADDRESS != NULL;
}

int ml_getSamplesPeriod() {
    const ml_model_header_t* const model_header = (ml_model_header_t*)MODEL_ADDRESS;
    if (model_header == NULL) {
        return -1;
    }
    return model_header->samples_period;
}

int ml_getSamplesLength() {
    const ml_model_header_t* const model_header = (ml_model_header_t*)MODEL_ADDRESS;
    if (model_header == NULL) {
        return -1;
    }
    return model_header->samples_length;
}

int ml_getSampleDimensions() {
    const ml_model_header_t* const model_header = (ml_model_header_t*)MODEL_ADDRESS;
    if (model_header == NULL) {
        return -1;
    }
    return model_header->sample_dimensions;
}

int ml_getInputLength() {
    ml4f_header_t *ml4f_model = get_ml4f_model();
    if (ml4f_model == NULL) {
        return -1;
    }
    return ml4f_shape_elements(ml4f_input_shape(ml4f_model));
}

ml_labels_t* ml_getLabels() {
    static ml_labels_t labels = {
        .num_labels = 0,
        .labels = NULL
    };

    const ml_model_header_t* const model_header = (ml_model_header_t*)MODEL_ADDRESS;
    if (model_header == NULL) {
        labels.num_labels = 0;
        if (labels.labels != NULL) {
            free(labels.labels);
            labels.labels = NULL;
        }
        return NULL;
    }

    // Workout the addresses in flash from each label, there are as many strings
    // as indicated by model_header->number_of_labels, they start from address
    // model_header->labels and are null-terminated.
    uint32_t header_end = (uint32_t)model_header + model_header->header_size;
    const char* flash_labels[model_header->number_of_labels];
    flash_labels[0] = &model_header->labels[0];
    for (int i = 1; i < model_header->number_of_labels; i++) {
        // Find the end of the previous string by looking for the null terminator
        flash_labels[i] = flash_labels[i - 1];
        while (*flash_labels[i] != '\0' && (uint32_t)flash_labels[i] < header_end) {
            flash_labels[i]++;
        }
        if ((uint32_t)flash_labels[i] >= header_end) {
            // We reached the end of the header without finding the null terminator
            free(flash_labels);
            return NULL;
        }
        // Currently pointing to the null terminator, so point to the following string
        flash_labels[i]++;
    }
    // Check the last string is null terminated at the end of header
    if (*(char *)(header_end - 1) != '\0') {
        free(flash_labels);
        return NULL;
    }

    // First check if the labels are the same, if not we need to set them again
    bool set_labels = false;
    if (labels.num_labels == 0 || labels.labels == NULL) {
        set_labels = true;
    } else if (labels.num_labels != model_header->number_of_labels) {
        set_labels = true;
    } else {
        for (size_t i = 0; i < labels.num_labels; i++) {
            if (labels.labels[i] != flash_labels[i]) {
                set_labels = true;
                break;
            }
        }
    }
    if (set_labels) {
        // First clear them out if needed
        labels.num_labels = 0;
        if (labels.labels != NULL) {
            free(labels.labels);
        }
        // Then set them to point to the strings in flash
        labels.labels = (const char **)malloc(model_header->number_of_labels * sizeof(char *));
        if (labels.labels == NULL) {
            return NULL;
        }
        labels.num_labels = model_header->number_of_labels;
        for (size_t i = 0; i < labels.num_labels; i++) {
            labels.labels[i] = flash_labels[i];
        }
    }

    return &labels;
}

ml_prediction_t* ml_predict(const float *input) {
    static ml_prediction_t predictions = {
        .max_index = 0,
        .num_labels = 0,
        .labels = NULL,
        .predictions = NULL,
    };

    ml_labels_t* labels = ml_getLabels();
    if (labels == NULL) {
        return NULL;
    }

    // Check if we need to resize the predictions array
    if (predictions.num_labels != labels->num_labels) {
        if (predictions.predictions != NULL) {
            free(predictions.predictions);
        }
        predictions.num_labels = labels->num_labels;
        predictions.predictions = (float *)malloc(predictions.num_labels * sizeof(float));
        if (predictions.predictions == NULL) {
            predictions.num_labels = 0;
            return NULL;
        }
    }
    // Always update the labels in case they changed
    predictions.labels = labels->labels;

    ml4f_header_t* ml4f_model = get_ml4f_model();
    int r = ml4f_full_invoke(ml4f_model, input, predictions.predictions);
    if (r != 0) {
        return NULL;
    }

    predictions.max_index = ml4f_argmax(predictions.predictions, predictions.num_labels);

    return &predictions;
}
