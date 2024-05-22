/*
 * Reciever.h
 *
 *  Created on: May 14, 2024
 *      Author: Conor Schott
 */

#ifndef SRC_MOTOR_DRIVER_H_
#define SRC_MOTOR_DRIVER_H_

#include <stdint.h>          // Include standard integer types
#include "stm32f4xx_hal.h"   // Include STM32 HAL

typedef struct {
    uint32_t forward_channel;    // Channel for forward motion
    uint32_t backward_channel;   // Channel for backward motion
    TIM_HandleTypeDef *htim;     // Timer handle for PWM control
} MotorDriver; // Struct for motor driver configuration

// Function prototypes
void motor_enable(MotorDriver *motor); // Enable motor driver
void motor_disable(MotorDriver *motor); // Disable motor driver
void motor_set_duty_cycle(MotorDriver *motor, int16_t duty_cycle); // Set motor duty cycle
void motor_brake(MotorDriver *motor); // Apply brake to motor

#endif /* SRC_MOTOR_DRIVER_H_ */
