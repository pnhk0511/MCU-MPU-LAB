#ifndef __EX10_H
#define __EX10_H

#include "stm32f1xx_hal.h"

#define LED_PIN_START GPIO_PIN_4
#define LED_PIN_END GPIO_PIN_15
const uint16_t LED_PINS[12] = {
    GPIO_PIN_4,  // 0 o'clock
    GPIO_PIN_5,  // 1 o'clock
    GPIO_PIN_6,  // 2 o'clock
    GPIO_PIN_7,  // 3 o'clock
    GPIO_PIN_8,  // 4 o'clock
    GPIO_PIN_9,  // 5 o'clock
    GPIO_PIN_10, // 6 o'clock
    GPIO_PIN_11, // 7 o'clock
    GPIO_PIN_12, // 8 o'clock
    GPIO_PIN_13, // 9 o'clock
    GPIO_PIN_14, // 10 o'clock
    GPIO_PIN_15  // 11 o'clock
};
void Update_LED_Display(uint8_t hour, uint8_t minute, uint8_t second) {
    for (uint8_t i = 0; i < 12; i++) {
        HAL_GPIO_WritePin(GPIOA, LED_PINS[i], GPIO_PIN_RESET);
    }
    if (hour < 12) {
        HAL_GPIO_WritePin(GPIOA, LED_PINS[hour], GPIO_PIN_SET);
    }
    if (minute < 12) {
        HAL_GPIO_WritePin(GPIOA, LED_PINS[minute], GPIO_PIN_SET);
    }
    if (second < 12) {
        HAL_GPIO_WritePin(GPIOA, LED_PINS[second], GPIO_PIN_SET);
    }
}
void Get_Current_Time(uint8_t *hour, uint8_t *minute, uint8_t *second) {
    *hour = 3;    // Example hour
    *minute = 7;  // Example minute
    *second = 10; // Example second
}
void Increment_Time(uint8_t *hour, uint8_t *minute, uint8_t *second) {
    (*second)++;
    if (*second >= 12) {
        (*minute)++;
        if (*minute >= 12) {
            *minute = 0;
            (*hour)++;
            if (*hour >= 12) {
                *hour = 0;
            }
        }
    }
}

#endif // __EX10_H
