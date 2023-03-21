/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*
 *@Note
 task1 and task2 alternate printing
*/

#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"

/* Global define */
#define TASK1_TASK_PRIO 5
#define TASK1_STK_SIZE 256
#define TASK2_TASK_PRIO 5
#define TASK2_STK_SIZE 256

/* Global Variable */
TaskHandle_t Task1Task_Handler;
TaskHandle_t Task2Task_Handler;

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0/1
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOA, &GPIO_InitStructure);

    // UserKey
    GPIO_InitStructure.GPIO_Pin = USER_KEY_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USER_KEY_GPIO_PORT, &GPIO_InitStructure);

    // LED1
    GPIO_InitStructure.GPIO_Pin = USER_LED1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USER_LED1_GPIO_PORT, &GPIO_InitStructure);

    // LED2
    GPIO_InitStructure.GPIO_Pin = USER_LED2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USER_LED2_GPIO_PORT, &GPIO_InitStructure);
}

uint8_t key_filt_val = 0;
uint8_t last_filt_key_state = 0;
uint8_t old_key_state = 0;
uint8_t aaa = 0;

/*********************************************************************
 * @fn      task1_task
 *
 * @brief   task1 program.
 *
 * @param  *pvParameters - Parameters point of task1
 *
 * @return  none
 */
void task1_task(void *pvParameters)
{
    uint8_t key_state = 0;
    while (1)
    {
        key_state = !GPIO_ReadInputDataBit(USER_KEY_GPIO_PORT, USER_KEY_GPIO_PIN);

        key_filt_val <<= 2;
        if (last_filt_key_state == key_state)
        {
            key_filt_val |= 0x03;
        }
        last_filt_key_state = key_state;

        if (key_filt_val == 0xFF)
        {
            if ((old_key_state == Bit_RESET) && (key_state == Bit_SET))
            {
                aaa++;
                printf("key press!!! aaa=%d\r\n", aaa);
            }

            old_key_state = key_state;
        }

        vTaskDelay(10);

        // printf("task1 entry\r\n");
        // GPIO_ResetBits(USER_LED1_GPIO_PORT, USER_LED1_GPIO_PIN);
        // GPIO_SetBits(USER_LED2_GPIO_PORT, USER_LED2_GPIO_PIN);
        // vTaskDelay(250);
        // GPIO_SetBits(USER_LED1_GPIO_PORT, USER_LED1_GPIO_PIN);
        // GPIO_ResetBits(USER_LED2_GPIO_PORT, USER_LED2_GPIO_PIN);
        // vTaskDelay(250);

        // if (GPIO_ReadInputDataBit(USER_KEY_GPIO_PORT, USER_KEY_GPIO_PIN))
        // {
        //     GPIO_ResetBits(USER_LED1_GPIO_PORT, USER_LED1_GPIO_PIN);
        //     GPIO_SetBits(USER_LED2_GPIO_PORT, USER_LED2_GPIO_PIN);
        // }
        // else
        // {
        //     GPIO_SetBits(USER_LED1_GPIO_PORT, USER_LED1_GPIO_PIN);
        //     GPIO_ResetBits(USER_LED2_GPIO_PORT, USER_LED2_GPIO_PIN);
        // }
        // vTaskDelay(10);
    }
}

/*********************************************************************
 * @fn      task2_task
 *
 * @brief   task2 program.
 *
 * @param  *pvParameters - Parameters point of task2
 *
 * @return  none
 */
void task2_task(void *pvParameters)
{
    while (1)
    {
        // printf("task2 entry\r\n");
        GPIO_ResetBits(GPIOC, GPIO_Pin_2);
        vTaskDelay(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_2);
        vTaskDelay(500);
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("FreeRTOS Kernel Version:%s\r\n", tskKERNEL_VERSION_NUMBER);

    GPIO_Toggle_INIT();
    /* create two task */
    xTaskCreate((TaskFunction_t)task2_task,
                (const char *)"task2",
                (uint16_t)TASK2_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_TASK_PRIO,
                (TaskHandle_t *)&Task2Task_Handler);

    xTaskCreate((TaskFunction_t)task1_task,
                (const char *)"task1",
                (uint16_t)TASK1_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_TASK_PRIO,
                (TaskHandle_t *)&Task1Task_Handler);
    vTaskStartScheduler();

    while (1)
    {
        printf("shouldn't run at here!!\n");
    }
}
