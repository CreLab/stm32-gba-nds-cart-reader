#include "stm32_data_mock.hpp"

HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;
volatile uint32_t uwTick = 0;

void HAL_IncTick(void)
{
    uwTick += uwTickFreq;
}

uint32_t HAL_GetTick(void)
{
    return uwTick++;
}

void HAL_Delay(uint32_t Delay)
{
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = Delay;

    /* Add a freq to guarantee minimum wait */
    if (wait < HAL_MAX_DELAY)
    {
        wait += (uint32_t)(uwTickFreq);
    }

    while ((HAL_GetTick() - tickstart) < wait)
    {
        HAL_IncTick();
    }
}

void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    (void)IRQn;
    (void)PreemptPriority;
    (void)SubPriority;
}

void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    (void)IRQn;
}

void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    (void)IRQn;
}

void HAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    (void)GPIOx;
    (void)GPIO_Init;
}

void HAL_GPIO_DeInit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    (void)GPIOx;
    (void)GPIO_Pin;
}

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
    (void)huart;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    (void)huart;
    (void)pData;
    (void)Size;
    (void)Timeout;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_Init(PCD_HandleTypeDef *hpcd)
{
    (void)hpcd;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_DeInit(PCD_HandleTypeDef *hpcd)
{
    (void)hpcd;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_SetAddress(PCD_HandleTypeDef *hpcd, uint8_t address)
{
    (void)hpcd;
    (void)address;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd)
{
    (void)hpcd;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_Stop(PCD_HandleTypeDef *hpcd)
{
    (void)hpcd;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_Open(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
    (void)hpcd;
    (void)ep_addr;
    (void)ep_mps;
    (void)ep_type;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_Close(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
    (void)hpcd;
    (void)ep_addr;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_Receive(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
    (void)hpcd;
    (void)ep_addr;
    (void)pBuf;
    (void)len;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_Transmit(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len)
{
    (void)hpcd;
    (void)ep_addr;
    (void)pBuf;
    (void)len;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_SetStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
    (void)hpcd;
    (void)ep_addr;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_ClrStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
    (void)hpcd;
    (void)ep_addr;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PCD_EP_Flush(PCD_HandleTypeDef *hpcd, uint8_t ep_addr)
{
    (void)hpcd;
    (void)ep_addr;

    return HAL_OK;
}

uint32_t HAL_PCD_EP_GetRxCount(PCD_HandleTypeDef const *hpcd, uint8_t ep_addr)
{
    (void)hpcd;
    (void)ep_addr;

    return HAL_OK;
}

HAL_StatusTypeDef  HAL_PCDEx_PMAConfig(PCD_HandleTypeDef *hpcd, uint16_t ep_addr, uint16_t ep_kind, uint32_t pmaadress)
{
    (void)hpcd;
    (void)ep_addr;
    (void)ep_kind;
    (void)pmaadress;

    return HAL_OK;
}