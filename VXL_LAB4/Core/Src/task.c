/*
 *
 *
 *
 *
 */

#include "task.h"

void LED1Blinky(void) {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void LED2Blinky(void) {
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

void LED3Blinky(void) {
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

void LED4Blinky(void) {
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void LED5Blinky(void) {
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}


