#ifndef __EX6_H
#define __EX6_H

#include "stm32f1xx_hal.h"

#define LED_PIN_START GPIO_PIN_4
#define LED_PIN_END GPIO_PIN_15
d Show_LED(uint8_t hour);
void clearAllClock(void);

void clearAllClock(void) {
    for (int pin = LED_PIN_START; pin <= LED_PIN_END; pin++) {
        HAL_GPIO_WritePin(GPIOA, pin, GPIO_PIN_RESET); // Set all pins low
    }
}

void Show_LED(uint8_t hour) {
    clearAllClock();
    // Turn on the LEDs
    uint16_t led_pin = LED_PIN_START << hour;
    HAL_GPIO_WritePin(GPIOA, led_pin, GPIO_PIN_SET);
}

#endif // __EX6_H
