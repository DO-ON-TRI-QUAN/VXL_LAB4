/*
 *
 *
 *
 *
 */

#include "task.h"
#include <stdio.h>
#include <string.h>

int get_time(void) {
	counter += 10;
	return counter;
}

void LED1Blinky(void) {
    char messageBuffer[64];
    char buffer[64];

    currentTime = HAL_GetTick() / 10 * 10;

    sprintf(messageBuffer, "Task 1 has started at: %d \r\n", currentTime);

    sprintf(buffer, "Counter value: %d \r\n", counter);

    HAL_UART_Transmit(&huart1, (uint8_t*)messageBuffer, strlen(messageBuffer), 100);

    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 100);

    // Toggle LED
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void LED2Blinky(void) {
    char messageBuffer[64];

    sprintf(messageBuffer, "Task 2 has started at: %d \r\n", currentTime);

    HAL_UART_Transmit(&huart1, (uint8_t*)messageBuffer, strlen(messageBuffer), 100);

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


