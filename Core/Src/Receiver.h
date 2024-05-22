/*
 * rc.h
 *
 *  Created on: May 16, 2024
 *      Author: Conor Schott
 */

#ifndef SRC_RC_H_
#define SRC_RC_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

// Declare global variables for trigger and wheel values
extern uint16_t g_trigger_val; // Global variable for trigger value
extern uint16_t g_wheel_val;   // Global variable for wheel value

// Struct to hold RC receiver configuration
typedef struct {
    uint32_t Trigger_Channel1_Rise; // Trigger channel for rising edge capture
    uint32_t Trigger_Channel1_Fall; // Trigger channel for falling edge capture
    uint32_t Trigger_Channel2_Rise; // Wheel channel for rising edge
    uint32_t Trigger_Channel2_Fall; // Wheel channel for falling edge
    TIM_HandleTypeDef* htim;        // Pointer to the timer handle used
    uint32_t nominalPWM;            // Nominal PWM from the receiver (in microseconds)
    uint32_t highPWM;               // High PWM period value from the receiver (in microseconds)
    uint32_t lowPWM;                // Low PWM period value from the receiver (in microseconds)
} RCReceiver;

// Function prototypes
void startRCReceiverCapture(RCReceiver* p_rc); // Function to start RC receiver capture
void calculateTriggerValueCallback(RCReceiver* p_rc, uint16_t previousWheelValue); // Function to calculate trigger value
void calculateWheelValueCallback(RCReceiver* p_rc, uint16_t previousWheelValue); // Function to calculate wheel value

#endif /* SRC_RC_H_ */
