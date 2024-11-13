/*
 *
 *
 *
 *
 */

#include "task.h"
#include <stdio.h>
#include <string.h>

void LED1Blinky(void) {
    char message[64] = "Task 1 has started at: ";
    char buffer[16];

    int current_time = HAL_GetTick() / 10 * 10;

    // Print start message with current time
    HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), 100);

    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, sprintf(buffer , "%d" , current_time), 100);

    HAL_UART_Transmit(&huart1, (uint8_t*)"\r" , 2, 100);

    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

}

void LED2Blinky(void) {
    char message[64] = "Task 2 has started at: ";
    char buffer[16];

    int current_time = HAL_GetTick() / 10 * 10;

    // Print start message with current time
    HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), 100);

    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, sprintf(buffer , "%d" , current_time), 100);

    HAL_UART_Transmit(&huart1, (uint8_t*)"\r" , 2, 100);

    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

}

//void LED1Blinky(void) {
	//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//}

//void LED2Blinky(void) {
	//HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//}

void LED3Blinky(void) {
	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
}

void LED4Blinky(void) {
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}

void LED5Blinky(void) {
	HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
}


