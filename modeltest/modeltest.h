/**
 * @brief Functions to run pre-recorded accelerometer data through the
 * built-in filters and model.
 *
 * @copyright
 * Copyright 2024 Micro:bit Educational Foundation.
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "mlrunner.h"
#include "testdata.h"

void testModel(const ml_actions_t *actions, ml_predictions_t *predictions);
