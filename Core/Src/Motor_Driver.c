/*
 * Receiver.c
 *
 *  Created on: May 14, 2024
 *      Author: Conor Schott
 */

#include "stm32f4xx_hal.h"
#include "Motor_Driver.h"

#define MAX_DUTY_CYCLE 4799 // Define maximum duty cycle value

/**
 * @brief Function to apply brake to the motor.
 * 
 * @param motor Pointer to the MotorDriver structure.
 */
void motor_brake(MotorDriver *motor) {
    // Stop PWM for both forward and backward channels
    __HAL_TIM_SET_COMPARE(motor->htim, motor->forward_channel, 1); // Set forward channel to minimal duty cycle
    __HAL_TIM_SET_COMPARE(motor->htim, motor->forward_channel, 1); // Set backward channel to minimal duty cycle
}

/**
 * @brief Function to enable the motor driver.
 * 
 * @param motor Pointer to the MotorDriver structure.
 */
void motor_enable(MotorDriver *motor) {
    // Start PWM for both forward and backward channels
    HAL_TIM_PWM_Start(motor->htim, motor->forward_channel);
    HAL_TIM_PWM_Start(motor->htim, motor->backward_channel);
}

/**
 * @brief Function to disable the motor driver.
 * 
 * @param motor Pointer to the MotorDriver structure.
 */
void motor_disable(MotorDriver *motor) {
    // Stop PWM for both forward and backward channels
    HAL_TIM_PWM_Stop(motor->htim, motor->forward_channel);
    HAL_TIM_PWM_Stop(motor->htim, motor->backward_channel);
}

/**
 * @brief Function to set the duty cycle of the motor.
 * 
 * @param motor Pointer to the MotorDriver structure.
 * @param duty_cycle Desired duty cycle (-MAX_DUTY_CYCLE to MAX_DUTY_CYCLE).
 */
void motor_set_duty_cycle(MotorDriver *motor, int16_t duty_cycle) {
    // Check if duty cycle is within valid range (-MAX_DUTY_CYCLE to MAX_DUTY_CYCLE)
    if (duty_cycle > MAX_DUTY_CYCLE) {
        duty_cycle = MAX_DUTY_CYCLE; // Limit duty cycle to maximum value
    } else if (duty_cycle < -MAX_DUTY_CYCLE) {
        duty_cycle = -MAX_DUTY_CYCLE; // Limit duty cycle to minimum value
    }

    // Set duty cycle for forward and backward channels based on sign of duty_cycle
    if (duty_cycle > 0) {
        // Forward motion
        __HAL_TIM_SET_COMPARE(motor->htim, motor->forward_channel, duty_cycle);
        __HAL_TIM_SET_COMPARE(motor->htim, motor->backward_channel, 0); // Set backward channel to 0
    } else if (duty_cycle < 0) {
        // Backward motion
        __HAL_TIM_SET_COMPARE(motor->htim, motor->forward_channel, 0); // Set forward channel to 0
        __HAL_TIM_SET_COMPARE(motor->htim, motor->backward_channel, -duty_cycle);
    } else {
        // Stop motion
        __HAL_TIM_SET_COMPARE(motor->htim, motor->forward_channel, 0);
        __HAL_TIM_SET_COMPARE(motor->htim, motor->backward_channel, 0); // Set backward channel to 0
    }
}
