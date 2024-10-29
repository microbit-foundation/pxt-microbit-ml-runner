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

// This combined function is more efficient than calling filterMean and filterStdDev separately
static inline void calcMeanAndStdDev(const float *data_in, const int in_size, float *mean, float *std_dev) {
    float sum = 0;
    for (int i = 0; i < in_size; i++) {
        sum += data_in[i];
    }
    const float _mean = sum / (float)in_size;

    float sum_of_squares = 0;
    for (int i = 0; i < in_size; i++) {
        float f = data_in[i] - _mean;
        sum_of_squares += f * f;
    }
    *std_dev = sqrtf(sum_of_squares / (float)in_size);
    *mean = _mean;
}

// Count the number of peaks
MldpReturn_t filterPeaks(const float *data_in, const int in_size, float *data_out, const int out_size) {
    const int lag = 5;
    const float threshold = 3.5;
    const float influence = 0.5;

    if (in_size < (5 + 2) || out_size != 1) {
        return MLDP_ERROR_CONFIG;
    }

    // Keep memory allocated between calls to avoid malloc/free overhead
    static float *filtered_y = NULL;
    static int alloc_size = 0;
    if (alloc_size < in_size) {
        free(filtered_y);
        filtered_y = (float *)malloc(in_size * sizeof(float));
        if (filtered_y == NULL) {
            alloc_size = 0;
            return MLDP_ERROR_ALLOC;
        }
        alloc_size = in_size;
    }
    memcpy(filtered_y, data_in, lag * sizeof(float));

    float mean_lag, std_dev_lag;
    calcMeanAndStdDev(filtered_y, lag, &mean_lag, &std_dev_lag);

    int previous_signal = 0;
    int peaksCounter = 0;
    for (int i = lag; i < in_size; i++) {
        int current_signal;
        const float diff = fabsf(data_in[i] - mean_lag);
        if (
            diff > 0.1f &&
            diff > threshold * std_dev_lag
        ) {
            if (data_in[i] > mean_lag) {
                current_signal = +1; // positive signal
                if (previous_signal == 0) {
                    peaksCounter++;
                }
            } else {
                current_signal = -1; // negative signal
            }
            // make influence lower
            filtered_y[i] = influence * data_in[i] + (1.0f - influence) * filtered_y[i - 1];
        } else {
            current_signal = 0; // no signal
            filtered_y[i] = data_in[i];
        }
        previous_signal = current_signal;

        // adjust the filters
        calcMeanAndStdDev(&filtered_y[i - lag], lag, &mean_lag, &std_dev_lag);
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
