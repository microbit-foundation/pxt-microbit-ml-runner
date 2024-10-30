#include <pxt.h>
#include "modeltest.h"
#include "mldataprocessor.h"
//#include "testdata.h"
//#include "testoutput.h"

#define DBG_PRINT(...)    uBit.serial.printf(__VA_ARGS__)


static void runModelTest(
    const ml_actions_t *actions, ml_predictions_t *predictions,
    const float *test_filter, const float *test_model
) {
    const unsigned int time_start = uBit.systemTime();

    float *modelData = mlDataProcessor.getProcessedData();
    if (modelData == NULL) {
        DBG_PRINT("Failed to processed data for the model\n");
        uBit.panic(899);
    }
    const size_t processDataSize = mlDataProcessor.getProcessedDataSize();

    // TODO: Uncomment to send the expected data to the model to check if
    // the model output is as expected
    // modelData = (float *)test_filter;

    // Print the processed data, compare it and print the expected values
    DBG_PRINT("Processed data:\t\t");
    for (size_t i = 0; i < processDataSize; i++) {
        int modelDataValue = modelData[i] * 100000;
        int expectedDataValue = test_filter[i] * 100000;
        DBG_PRINT("%d", modelDataValue);
        if (abs(modelDataValue - expectedDataValue) > abs(expectedDataValue * 0.01)) {
            DBG_PRINT("!");
        } else {
            DBG_PRINT(" ");
        }
        DBG_PRINT(", ", modelDataValue);
        if ((i +1) % 3 == 0) {
            DBG_PRINT("\t\t");
        }
    }

    DBG_PRINT("\nExpected data:\t\t");
    for (size_t i = 0; i < processDataSize; i++) {
        int expectedDataValue = test_filter[i] * 100000;
        DBG_PRINT("%d , ", expectedDataValue);
        if ((i +1) % 3 == 0) {
            DBG_PRINT("\t\t");
        }
    }
    DBG_PRINT("\n");

    bool success = ml_predict(modelData, processDataSize, actions, predictions);
    if (!success) {
        DBG_PRINT("Failed to run model\n");
        uBit.panic(897);
    }

    // Print the model output
    DBG_PRINT("Model output:\t\t");
    for (size_t i = 0; i < actions->len; i++) {
        DBG_PRINT("%s[%d.%d] ",
                  actions->action[i].label,
                  (int)(predictions->prediction[i] * 100),
                  (int)(predictions->prediction[i] * 1000) % 10);
    }
    DBG_PRINT("\n");

    // Print the expected results and track the maximum difference
    DBG_PRINT("Expected Model:\t\t");
    int maxModelDiff = 0;
    for (size_t i = 0; i < actions->len; i++) {
        int expectedResult = test_model[i] * 1000;
        int actualResult = predictions->prediction[i] * 1000;
        DBG_PRINT("%s[%d.%d] ", actions->action[i].label, expectedResult / 10, expectedResult % 10);
        maxModelDiff = max(abs(expectedResult - actualResult), maxModelDiff);
    }
    if (maxModelDiff > 0) {
        DBG_PRINT("\nModel output diff:\t%d.%d %%\n", maxModelDiff / 10, maxModelDiff % 10);
    }
    DBG_PRINT("\n\n");
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void testModel(const ml_actions_t *actions, ml_predictions_t *predictions) {
    if (mlDataProcessor.getProcessedDataSize() != ML_TEST_FILTER_OUTPUT_SIZE) {
        DBG_PRINT("Invalid processed data size: %d\n", mlDataProcessor.getProcessedDataSize());
        uBit.panic(890);
    }

    // Input the pre-recorded data into the filters and
    // run the model inference for each of the recordings
    for (size_t recordingIndex = 0; recordingIndex < ML_TEST_RECORDINGS; recordingIndex++) {
        DBG_PRINT("Recording %d\n", recordingIndex);
        for (size_t sample = 0; sample < ML_TEST_RECORDING_SIZE; sample++) {
            const float testData[3] = {
                test_data_x[recordingIndex][sample],
                test_data_y[recordingIndex][sample],
                test_data_z[recordingIndex][sample],
            };
            MldpReturn_t recordDataResult = mlDataProcessor.recordData(testData, 3);
            if (recordDataResult != MLDP_SUCCESS) {
                DBG_PRINT("Failed to record test accelerometer data\n");
                uBit.panic(892);
            }
        }
        runModelTest(
            actions,
            predictions,
            (const float *)&test_filter_output[recordingIndex][0],
            (const float *)&test_model_output[recordingIndex][0]
        );
    }
}
#pragma GCC pop_options
