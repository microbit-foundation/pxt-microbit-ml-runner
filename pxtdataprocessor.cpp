
#include <math.h>
#include <cstring>
#include "PxtDataProcessor.h"

// To represent the accelerometer data x, y, z
static const int DATA_AXIS = 3;

/**************************************************************************************************/
/* Filters                                                                                        */
/*                                                                                                */
/* Adapted from:                                                                                  */
/*   https://github.com/microbit-foundation/ml-trainer/blob/v0.6.0/src/script/datafunctions.ts    */
/*   (c) 2023, Center for Computational Thinking and Design at Aarhus University and contributors */
/*   SPDX-License-Identifier: MIT                                                                 */
/**************************************************************************************************/
static float filterMax(float *data, int size) {
    float max = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

static float filterMin(float *data, int size) {
    float min = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    return min;
}

static float filterMean(float *data, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

// Standard Deviation
static float filterStdDev(float *data, int size) {
    float mean = filterMean(data, size);
    float std = 0;
    for (int i = 0; i < size; i++) {
        std += (data[i] - mean) * (data[i] - mean);
    }
    std /= size;
    return sqrt(std);
}

// Count the number of peaks
// Warning! This can allocate 5x the size of the data in the stack
// so ensure DEVICE_STACK_SIZE is appropriately set
// TODO: Move to the heap, pxt automatically uses its allocator
static float filterPeaks(float *data, int size) {
    const int lag = 5;
    const float threshold = 3.5;
    const float influence = 0.5;
    int peaksCounter = 0;

    float signals[size];
    float filteredY[size];
    float lead_in[lag];
    float avgFilter[size];
    float stdFilter[size];
    memset(signals, 0, size * sizeof(float));
    memcpy(filteredY, data, size * sizeof(float));
    memcpy(lead_in, data, lag * sizeof(float));
    avgFilter[lag - 1] = filterMean(lead_in, lag);
    stdFilter[lag - 1] = filterStdDev(lead_in, lag);

    for (int i = lag; i < size; i++) {
        if (fabs(data[i] - avgFilter[i - 1]) > 0.1 &&
            fabs(data[i] - avgFilter[i - 1]) > threshold * stdFilter[i - 1]
        ) {
            if (data[i] > avgFilter[i - 1]) {
                signals[i] = +1; // positive signal
                if (i - 1 > 0 && signals[i - 1] == 0) {
                    peaksCounter++;
                }
            } else {
                signals[i] = -1; // negative signal
            }
            // make influence lower
            filteredY[i] = influence * data[i] + (1 - influence) * filteredY[i - 1];
        } else {
            signals[i] = 0; // no signal
            filteredY[i] = data[i];
        }

        // adjust the filters
        float y_lag[lag];
        memcpy(y_lag, &filteredY[i - lag], lag * sizeof(float));
        avgFilter[i] = filterMean(y_lag, lag);
        stdFilter[i] = filterStdDev(y_lag, lag);
    }
    return peaksCounter;
}

// Total Absolute Acceleration
static float filterTotalAcc(float *data, int size) {
    float total = 0;
    for (int i = 0; i < size; i++) {
        total += fabs(data[i]);
    }
    return total;
}

// Zero Crossing Rate
static float filterZcr(float *data, int size) {
    int count = 0;
    for (int i = 1; i < size; i++) {
        if ((data[i] >= 0 && data[i - 1] < 0) ||
            (data[i] < 0 && data[i - 1] >= 0)) {
            count++;
        }
    }
    return count / (size - 1);

}

// Root Mean Square
static float filterRms(float *data, int size) {
    float rms = 0;
    for (int i = 0; i < size; i++) {
        rms += data[i] * data[i];
    }
    rms /= size;
    return sqrt(rms);
}

// Order is important for the outputData as set in:
// https://github.com/microbit-foundation/ml-trainer/blob/v0.6.0/src/script/stores/mlStore.ts#L122-L131
static float (*filters[])(float*, int) = {
    filterMax,
    filterMean,
    filterMin,
    filterStdDev,
    filterPeaks,
    filterTotalAcc,
    filterZcr,
    filterRms,
};

/*****************************************************************************/
/* PxtDataProcessor                                                          */
/*****************************************************************************/
PxtDataProcessor::PxtDataProcessor(int samples) {
    accDataX = new float[samples];
    accDataY = new float[samples];
    accDataZ = new float[samples];
    accSamples = samples;
    accDataIndex = 0;
    filterSize = sizeof(filters) / sizeof(filters[0]);
    outputData = new float[filterSize * DATA_AXIS];
}

PxtDataProcessor::~PxtDataProcessor() {
    delete[] accDataX;
    delete[] accDataY;
    delete[] accDataZ;
    delete[] outputData;
}

void PxtDataProcessor::recordAccData(int x, int y, int z) {
    accDataX[accDataIndex] = x / 1000.0f;
    accDataY[accDataIndex] = y / 1000.0f;
    accDataZ[accDataIndex] = z / 1000.0f;
    accDataIndex++;
    if (accDataIndex >= accSamples) {
        accDataIndex = 0;
    }
}

bool PxtDataProcessor::isDataReady() {
    return accDataIndex == 0;
}

float* PxtDataProcessor::getModelInputData() {
    // Apply all filter to outputData
    for (int i = 0; i < filterSize; i++) {
        outputData[i*DATA_AXIS + 0] = filters[i](accDataX, accSamples);
        outputData[i*DATA_AXIS + 1] = filters[i](accDataY, accSamples);
        outputData[i*DATA_AXIS + 2] = filters[i](accDataZ, accSamples);
    }
    return outputData;
}
