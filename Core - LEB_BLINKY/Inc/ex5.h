#ifndef INC_EX3_SEG7_H_
#define INC_EX3_SEG7_H_

#include "stm32f1xx_hal.h"

// Define GPIO pins for LEDs
#define LED_RED1 GPIO_PIN_0
#define LED_YELLOW1 GPIO_PIN_1
#define LED_GREEN1 GPIO_PIN_2
#define LED_RED2 GPIO_PIN_8
#define LED_YELLOW2 GPIO_PIN_7
#define LED_GREEN2 GPIO_PIN_6

// Define GPIO pins for the 7-segment display
#define SEG_A GPIO_PIN_8
#define SEG_B GPIO_PIN_9
#define SEG_C GPIO_PIN_10
#define SEG_D GPIO_PIN_11
#define SEG_E GPIO_PIN_12
#define SEG_F GPIO_PIN_13
#define SEG_G GPIO_PIN_14

// Define traffic light states for the 2-way system
typedef enum {
    RED1_GREEN2_STATE,   // Step 1: Red 1 ON, Green 2 ON
    YELLOW2_STATE,       // Step 2: Yellow 2 ON, Green 2 OFF
    RED2_GREEN1_STATE,   // Step 3: Red 2 ON, Green 1 ON
    YELLOW1_STATE        // Step 4: Yellow 1 ON, Green 1 OFF
} TrafficLightState;

TrafficLightState currentState = RED1_GREEN2_STATE;
uint8_t stateCounter = 0;

// Define countdown states
typedef enum {
    COUNT_RUNNING,
    COUNT_COMPLETE
} Count;

Count count;
int countValue = 0;

// Function prototypes
void traffic_light_init(void);
void seg7_init(void);
void display7SEG(int num);
void traffic_light_update(void);
void countdown_and_display(int seconds);

// Function implementations

// Initialize traffic light pins
void traffic_light_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOB clock for LEDs
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure GPIO pins for the LEDs
    GPIO_InitStruct.Pin = LED_RED1 | LED_YELLOW1 | LED_GREEN1 | LED_RED2 | LED_YELLOW2 | LED_GREEN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Set initial state to RED1_GREEN2_STATE
    currentState = RED1_GREEN2_STATE;
    stateCounter = 0;
}

// Initialize 7-segment display pins
void seg7_init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA clock for 7-segment
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

// Function to display a number on 7-segment display
void display7SEG(int num) {
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

// Traffic light state machine with countdown
void traffic_light_update(void) {
    switch (currentState) {
        case RED1_GREEN2_STATE:
            HAL_GPIO_WritePin(GPIOB, LED_RED1, GPIO_PIN_SET);       // Red 1 ON
            HAL_GPIO_WritePin(GPIOB, LED_GREEN2, GPIO_PIN_SET);     // Green 2 ON
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW1 | LED_YELLOW2 | LED_RED2 | LED_GREEN1, GPIO_PIN_RESET);

            countdown_and_display(5);  // 5-second countdown for Red
            currentState = RED2_GREEN1_STATE;
            break;

        case RED2_GREEN1_STATE:
            HAL_GPIO_WritePin(GPIOB, LED_RED2, GPIO_PIN_SET);       // Red 2 ON
            HAL_GPIO_WritePin(GPIOB, LED_GREEN1, GPIO_PIN_SET);     // Green 1 ON
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW1 | LED_YELLOW2 | LED_RED1 | LED_GREEN2, GPIO_PIN_RESET);

            countdown_and_display(3);  // 5-second countdown for Red
            currentState = YELLOW1_STATE;
            break;

        case YELLOW1_STATE:
            HAL_GPIO_WritePin(GPIOB, LED_GREEN1, GPIO_PIN_RESET);   // Green 1 OFF
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW1, GPIO_PIN_SET);    // Yellow 1 ON

            countdown_and_display(2);  // 2-second countdown for Yellow
            currentState = RED1_GREEN2_STATE;
            break;

        default:
            break;
    }
}

// Countdown timer with 7-segment display
void countdown_and_display(int seconds) {
    countValue = seconds;

    while (countValue > 0) {
        display7SEG(countValue);
        HAL_Delay(1000);  // 1-second delay
        countValue--;
    }
    display7SEG(0);  // Display 0 when countdown completes
}

#endif /* INC_EX3_SEG7_H_ */
