#ifndef EX1_H_
#define EX1_H_

#include "stm32f1xx_hal.h"

// Define LED pins
#define LED_RED_PIN GPIO_PIN_5
#define LED_YELLOW_PIN GPIO_PIN_6
#define LED_GREEN_PIN GPIO_PIN_7
#define LED_PORT GPIOA

// Define traffic light states
typedef enum {
    RED_STATE,
    YELLOW_STATE,
    GREEN_STATE
} TrafficLightState;

// Global variables
TrafficLightState currentState = RED_STATE;
uint8_t stateCounter = 0;

// Function prototypes
void TrafficLight_Init(void);
void TrafficLight_Run(void);

// Function implementations
void TrafficLight_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure GPIO pins for the LEDs
    GPIO_InitStruct.Pin = LED_RED_PIN | LED_YELLOW_PIN | LED_GREEN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    // Set initial state to RED
    currentState = RED_STATE;
    stateCounter = 0;
}

void TrafficLight_Run(void) {
    stateCounter++;

    switch (currentState) {
        case RED_STATE:
            // RED ON, YELLOW OFF, GREEN OFF
            HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, GPIO_PIN_RESET);       // RED ON
            HAL_GPIO_WritePin(LED_PORT, LED_YELLOW_PIN, GPIO_PIN_SET);  // YELLOW OFF
            HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, GPIO_PIN_SET);     // GREEN OFF (Negative control)

            if (stateCounter >= 5) {  // Stay in RED for 5 seconds
                currentState = YELLOW_STATE;
                stateCounter = 0;
            }
            break;

        case YELLOW_STATE:
            // RED OFF, YELLOW ON, GREEN OFF
            HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, GPIO_PIN_SET);     // RED OFF
            HAL_GPIO_WritePin(LED_PORT, LED_YELLOW_PIN, GPIO_PIN_RESET);    // YELLOW ON
            HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, GPIO_PIN_SET);     // GREEN OFF (Negative control)

            if (stateCounter >= 2) {  // Stay in YELLOW for 2 seconds
                currentState = GREEN_STATE;
                stateCounter = 0;
            }
            break;

        case GREEN_STATE:
            // RED OFF, YELLOW OFF, GREEN ON (Negative control)
            HAL_GPIO_WritePin(LED_PORT, LED_RED_PIN, GPIO_PIN_SET);     // RED OFF
            HAL_GPIO_WritePin(LED_PORT, LED_YELLOW_PIN, GPIO_PIN_SET);  // YELLOW OFF
            HAL_GPIO_WritePin(LED_PORT, LED_GREEN_PIN, GPIO_PIN_RESET);   // GREEN ON (Negative control)

            if (stateCounter >= 3) {  // Stay in GREEN for 3 seconds
                currentState = RED_STATE;
                stateCounter = 0;
            }
            break;

        default:
            break;
    }
}

#endif /* EX1_H_ */
