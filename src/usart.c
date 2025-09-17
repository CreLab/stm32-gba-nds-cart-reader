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

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (huart->Instance == USART1)
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

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    }
}

GLOBAL_STATUS uart_send_data(const void *data, uint16_t len)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (HAL_UART_Transmit(&huart1, (void *) data, len, HAL_MAX_DELAY) != HAL_OK)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_UART_TRANSMIT_FAIL);
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS uart_print_bytes(const void *data, uint16_t len)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (len > 64)
    {
        len = 64;
    }

    char out[256] = {0};
    out[0] = '\0';
    const char *input = data;

    while (len-- > 0)
    {
        strcat(out, itox8((uint8_t) *input++));
        strcat(out, ",");
    }

    CHECK_GLOBAL_STATUS(uart_printf("%s\r\n", out));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS uart_printf(const char *msg, ...)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    va_list args;
    va_start(args, msg);

    char out[256] = {0};
    int len = vsnprintf(out, sizeof(out), msg, args);
    CHECK_GLOBAL_STATUS(uart_send_data(out, (uint16_t) len));

    va_end(args);

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS print_keybuf(const char *pMsg, s_blowfish_t *pKeyBuf)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    const uint8_t *keybuf = (const uint8_t *) pKeyBuf;

    uart_printf("%s:\r\n", pMsg);

    for (size_t i = 0; i < sizeof(s_blowfish_t); i++)
    {
        uart_printf(" %02x", keybuf[i]);
    }

    CHECK_GLOBAL_STATUS(uart_printf("\r\n"));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS print_chip_id(const struct nds_chip_id *id)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    uint8_t bid[4];
    memcpy(bid, id, 4);
    CHECK_GLOBAL_STATUS(
            uart_printf("chip_id: %02x %02x %02x %02x\r\n", bid[0], bid[1], bid[2], bid[3]));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}
