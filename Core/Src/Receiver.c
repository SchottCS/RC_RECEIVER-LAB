/*
 * rc.c
 *
 *  Created on: May 16, 2024
 *      Author: Conor Schott
 */

#include "Receiver.h" // Include the header file defining RCReceiver struct
#include <string.h> // Include library for string manipulation functions
#include <stdlib.h> // Include library for standard utility functions

// Global variables to hold trigger and wheel values
uint16_t g_trigger_val = 0;
uint16_t g_wheel_val = 0;

/**
 * @brief Function to calculate the value considering overflow and below nominal detection.
 * 
 * @param previousValue The previous value to check.
 * @param highPWM The high PWM value threshold.
 * @param lowPWM The low PWM value threshold.
 * @param nominalPWM The nominal PWM value.
 * @return uint16_t The corrected value.
 */
static uint16_t calculateValue(uint16_t previousValue, uint32_t highPWM, uint32_t lowPWM, uint32_t nominalPWM) {
    if (previousValue > highPWM || previousValue < lowPWM) {
        return nominalPWM; // Reset to nominal if overflow or below nominal
    }
    return previousValue;
}

/**
 * @brief Function to start RC receiver capture.
 * 
 * @param rc Pointer to the RCReceiver structure.
 */
void startRCReceiverCapture(RCReceiver* rc) {
    // Start interrupt-based input capture for trigger and wheel channels
    HAL_TIM_IC_Start_IT(rc->htim, rc->Trigger_Channel1_Rise);
    HAL_TIM_IC_Start_IT(rc->htim, rc->Trigger_Channel1_Fall);
    HAL_TIM_IC_Start_IT(rc->htim, rc->Trigger_Channel2_Rise);
    HAL_TIM_IC_Start_IT(rc->htim, rc->Trigger_Channel2_Fall);
}

/**
 * @brief Callback function to handle trigger value calculation.
 * 
 * @param rc Pointer to the RCReceiver structure.
 * @param previousValue The previous value to check.
 */
void calculateTriggerValueCallback(RCReceiver* rc, uint16_t previousValue) {
    g_trigger_val = calculateValue(previousValue, rc->highPWM, rc->lowPWM, rc->nominalPWM);
}

/**
 * @brief Callback function to handle wheel value calculation.
 * 
 * @param rc Pointer to the RCReceiver structure.
 * @param previousValue The previous value to check.
 */
void calculateWheelValueCallback(RCReceiver* rc, uint16_t previousValue) {
    g_wheel_val = calculateValue(previousValue, rc->highPWM, rc->lowPWM, rc->nominalPWM);
}
