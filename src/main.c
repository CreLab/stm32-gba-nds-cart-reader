#include "util.h"
#include "usb_device.h"
#include "gba_cart.h"
#include "nds_cart.h"
#include "usbd_cdc_if.h"
#include "host_interface.h"
#include "usart.h"

GLOBAL_STATUS systemClockConfig(void);
void enableAllSystemClocks(void);

int main(void)
{
    HAL_Init();

    systemClockConfig();

    MX_USB_DEVICE_Init();
    MX_USART1_UART_Init();

    enableAllSystemClocks();

    gba_cart_init();
    nds_cart_init();

    HAL_Delay(1000);

    while(true)
    {
         hostInterface_run();
    }
}

GLOBAL_STATUS systemClockConfig(void)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_OSC_INIT_FAIL);
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_CLK_INIT_FAIL);
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_PERIPH_CLK_FAIL);
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

void enableAllSystemClocks(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_DISABLE();
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{ 
    uart_printf("ASSERT FAILED in file <%s> line #%lu\n", file, line);
}
#endif /* USE_FULL_ASSERT */
