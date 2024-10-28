/**
 * Functions to filter data in preparation for some ML models.
 *
 * Adapted from:
 *   https://github.com/microbit-foundation/ml-trainer/blob/v0.6.0/src/script/datafunctions.ts
 *   (c) 2023, Center for Computational Thinking and Design at Aarhus University and contributors
 *   SPDX-License-Identifier: MIT
 */
#include <math.h>
#include <string.h>
#include "mldataprocessor.h"

MldpReturn_t filterMax(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 1 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float max = data_in[0];
    for (int i = 1; i < in_size; i++) {
        if (data_in[i] > max) {
            max = data_in[i];
        }
    }
    *data_out = max;

    return MLDP_SUCCESS;
}

MldpReturn_t filterMin(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 1 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float min = data_in[0];
    for (int i = 1; i < in_size; i++) {
        if (data_in[i] < min) {
            min = data_in[i];
        }
    }
    *data_out = min;

    return MLDP_SUCCESS;
}

MldpReturn_t filterMean(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 1 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float sum = 0;
    for (int i = 0; i < in_size; i++) {
        sum += data_in[i];
    }
    *data_out = sum / (float)in_size;

    return MLDP_SUCCESS;
}

// Standard Deviation
MldpReturn_t filterStdDev(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 1 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float mean;
    MldpReturn_t mean_result = filterMean(data_in, in_size, &mean, 1);
    if (mean_result != MLDP_SUCCESS) {
        return mean_result;
    }

    float sum_of_squares = 0;
    for (int i = 0; i < in_size; i++) {
        float f = data_in[i] - mean;
        sum_of_squares += f * f;
    }
    *data_out = sqrtf(sum_of_squares / (float)in_size);

    return MLDP_SUCCESS;
}

// Count the number of peaks
// Warning! This can allocate 5x the in_size of the data in the stack
// so ensure DEVICE_STACK_SIZE is appropriately set
// TODO: Move to the heap, pxt automatically uses its allocator
MldpReturn_t filterPeaks(const float *data_in, const int in_size, float *data_out, const int out_size) {
    const int lag = 5;
    const float threshold = 3.5;
    const float influence = 0.5;

    if (in_size < (5 + 2) || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float signals[in_size];
    float filtered_y[in_size];
    float lead_in[lag];
    float avg_filter[in_size];
    float std_filter[in_size];
    memset(signals, 0, in_size * sizeof(float));
    memcpy(filtered_y, data_in, in_size * sizeof(float));
    memcpy(lead_in, data_in, lag * sizeof(float));

    float mean_lag, std_dev_lag;
    MldpReturn_t mean_result = filterMean(lead_in, lag, &mean_lag, 1);
    MldpReturn_t std_dev_result = filterStdDev(lead_in, lag, &std_dev_lag, 1);
    if (std_dev_result != MLDP_SUCCESS || mean_result != MLDP_SUCCESS) {
        return MLDP_ERROR_CONFIG;
    }

    avg_filter[lag - 1] = mean_lag;
    std_filter[lag - 1] = std_dev_lag;

    int peaksCounter = 0;
    for (int i = lag; i < in_size; i++) {
        if (fabsf(data_in[i] - avg_filter[i - 1]) > 0.1f &&
            fabsf(data_in[i] - avg_filter[i - 1]) > threshold * std_filter[i - 1]
        ) {
            if (data_in[i] > avg_filter[i - 1]) {
                signals[i] = +1; // positive signal
                if (i - 1 > 0 && signals[i - 1] == 0) {
                    peaksCounter++;
                }
            } else {
                signals[i] = -1; // negative signal
            }
            // make influence lower
            filtered_y[i] = influence * data_in[i] + (1.0f - influence) * filtered_y[i - 1];
        } else {
            signals[i] = 0; // no signal
            filtered_y[i] = data_in[i];
        }

        // adjust the filters
        float y_lag[lag];
        memcpy(y_lag, &filtered_y[i - lag], lag * sizeof(float));
        filterMean(y_lag, lag, &mean_lag, 1);
        filterStdDev(y_lag, lag, &std_dev_lag, 1);
        avg_filter[i] = mean_lag;
        std_filter[i] = std_dev_lag;
    }
    *data_out = peaksCounter;

    return MLDP_SUCCESS;
}

// Total Absolute Acceleration
MldpReturn_t filterTotalAcc(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 1 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float total = 0;
    for (int i = 0; i < in_size; i++) {
        total += fabsf(data_in[i]);
    }
    *data_out = total;

    return MLDP_SUCCESS;
}

// Zero Crossing Rate
MldpReturn_t filterZcr(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 2 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    int count = 0;
    for (int i = 1; i < in_size; i++) {
        if ((data_in[i] >= 0 && data_in[i - 1] < 0) ||
            (data_in[i] < 0 && data_in[i - 1] >= 0)) {
            count++;
        }
    }
    *data_out = (float)count / (float)(in_size - 1);

    return MLDP_SUCCESS;
}

// Root Mean Square
MldpReturn_t filterRms(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size < 1 || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    float rms = 0;
    for (int i = 0; i < in_size; i++) {
        rms += data_in[i] * data_in[i];
    }
    *data_out = sqrtf(rms / (float)in_size);

    return MLDP_SUCCESS;
}

MldpReturn_t filterPassThrough(const float *data_in, const int in_size, float *data_out, const int out_size) {
    if (in_size > out_size) {
        return MLDP_ERROR_CONFIG;
    }

    memcpy(data_out, data_in, in_size * sizeof(float));

    return MLDP_SUCCESS;
}
