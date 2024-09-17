/*
 * ex3.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Admin
 */

#ifndef INC_EX3_H_
#define INC_EX3_H_
#include "stm32f1xx_hal.h"
#define LED_RED1 GPIO_PIN_0
#define LED_YELLOW1 GPIO_PIN_1
#define LED_GREEN1 GPIO_PIN_2
#define LED_RED2 GPIO_PIN_8
#define LED_YELLOW2 GPIO_PIN_7
#define LED_GREEN2 GPIO_PIN_6

typedef enum {
    RED1_GREEN2_STATE,
    YELLOW2_STATE,
    RED2_GREEN1_STATE,
    YELLOW1_STATE
} TrafficLightState1;

TrafficLightState1 currentState1 = RED1_GREEN2_STATE;
uint8_t stateCounter1 = 0;

void ex3(void);

void ex3(void) {
    stateCounter++;
    switch (currentState) {
        case RED1_GREEN2_STATE:
            HAL_GPIO_WritePin(GPIOB, LED_RED1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_GREEN2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW1 | LED_YELLOW2 | LED_RED2 | LED_GREEN1, GPIO_PIN_RESET);  // Others OFF

            if (stateCounter >= 3) {
                currentState = YELLOW2_STATE;
                stateCounter = 0;
            }
            break;

        case YELLOW2_STATE:

            HAL_GPIO_WritePin(GPIOB, LED_GREEN2, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_RED1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_GREEN1, GPIO_PIN_RESET);

            if (stateCounter >= 2) {
                currentState = RED2_GREEN1_STATE;
                stateCounter = 0;
            }
            break;

        case RED2_GREEN1_STATE:
            HAL_GPIO_WritePin(GPIOB, LED_RED2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_GREEN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_RED1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW1 | LED_YELLOW2 | LED_GREEN2, GPIO_PIN_RESET);

            if (stateCounter >= 3) {
                currentState = YELLOW1_STATE;
                stateCounter = 0;
            }
            break;

        case YELLOW1_STATE:
            HAL_GPIO_WritePin(GPIOB, LED_GREEN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, LED_YELLOW1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, LED_RED2, GPIO_PIN_SET);

            if (stateCounter >= 2) {
                currentState = RED1_GREEN2_STATE;
                stateCounter = 0;
            }
            break;

        default:
            break;
    }
}



#endif /* INC_EX3_H_ */
