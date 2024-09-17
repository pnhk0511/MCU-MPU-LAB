/*
 * seg7.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Admin
 */

#ifndef INC_SEG7_H_
#define INC_SEG7_H_

#include "stm32f1xx_hal.h"

// Define GPIO pins for the 7-segment display
#define SEG_A GPIO_PIN_8
#define SEG_B GPIO_PIN_9
#define SEG_C GPIO_PIN_10
#define SEG_D GPIO_PIN_11
#define SEG_E GPIO_PIN_12
#define SEG_F GPIO_PIN_13
#define SEG_G GPIO_PIN_14

// Define the count states
typedef enum {
    COUNT_RUNNING,
    COUNT_COMPLETE
} Count;

Count count;
int countValue;

// Function prototypes
void seg7_init(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure GPIO pins for the 7-segment display
    GPIO_InitStruct.Pin = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Set initial state for count
    count = COUNT_COMPLETE;
    countValue = 0;
}
void display7SEG(int num){
    switch (num) {
        case 0:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_G, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, SEG_B | SEG_C, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_D | SEG_E | SEG_G, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_C | SEG_F, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_C | SEG_D | SEG_G, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_E | SEG_F, GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, SEG_B | SEG_C | SEG_F | SEG_G, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_D | SEG_E, GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_B | SEG_E, GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_B, GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_C, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_D | SEG_E | SEG_F | SEG_G, GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, SEG_E, GPIO_PIN_SET);
            break;
        default:
            HAL_GPIO_WritePin(GPIOA, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, GPIO_PIN_SET);
            break;
    }
}
void count_up(int seconds) {
    count = COUNT_RUNNING;
    countValue = 0;  // Start from 0

    while (countValue <= seconds) {
        display7SEG(countValue);
        HAL_Delay(1000);  // 1-second delay
        countValue++;

        // If we reach the target number, complete the countdown
        if (countValue > seconds) {
            count = COUNT_COMPLETE;
            break;
        }
    }
}

#endif /* INC_SEG7_H_ */
