#include "usart.h"
#include "util.h"

UART_HandleTypeDef huart1;

GLOBAL_STATUS MX_USART1_UART_Init(void)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_UART_INIT);
    }

    HAL_Delay(1000);

    uart_printf("UART Init Success\r\n");

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (uartHandle->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{
    if (uartHandle->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    }
}

UART_HandleTypeDef* Get_USART1_UART_Handle(void)
{
    return &huart1;
}

#ifdef ERROR_INTERRUPT_SIGNALS
void HAL_UART_DebugSignal(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void HAL_UART_DebugSignal_RX(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, state);
}

void HAL_UART_DebugSignal_TX(GPIO_PinState state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, state);
}

void HAL_UART_DebugPeriodSignal_RX(uint32_t time)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
    HAL_Delay(time);
}

void HAL_UART_DebugPeriodSignal_TX(uint32_t time)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
    HAL_Delay(time);
}
#endif