#ifndef __EX6_H
#define __EX6_H

#include "stm32f1xx_hal.h"

// Define macros for LED positions
#define LED_PIN_START GPIO_PIN_5
#define LED_PIN_END GPIO_PIN_4
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

void clearAllClock(void) {
    for (int pin = LED_PIN_START; pin <= LED_PIN_END; pin++) {
        HAL_GPIO_WritePin(GPIOA, pin, GPIO_PIN_RESET);
    }
}
void Show_LED(uint8_t hour) {
    clearAllClock();  // Turn off all LEDs first
    HAL_GPIO_WritePin(GPIOA, LED_PINS[hour], GPIO_PIN_SET);
}
void setNumberOnClock(int num) {
    if (num < 0 || num > 11) {
        return;  // Return if the number is out of bounds
    }
    clearAllClock();
    HAL_GPIO_WritePin(GPIOA, LED_PINS[num], GPIO_PIN_SET);
}
void clearNumberOnClock(int num) {
    if (num < 0 || num > 11) {
        return;  // Return if the number is out of bounds
    }
    HAL_GPIO_WritePin(GPIOA, LED_PINS[num], GPIO_PIN_RESET);
}

#endif // __EX6_H
