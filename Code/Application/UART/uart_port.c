
#include "hal_uart.h"
#include "uart_port.h"

#define APP_UARTPORT_BUF_LEN                    (128U)

static void _uart_port_rx_callback(uint8 port, uint8 event);
static uint8 uart_port_rx_buf[APP_UARTPORT_BUF_LEN];

/**
 * @brief UART Hareware initialize
 * @param none
 * @retval none
 */
void uart_port_init(void)
{
    halUARTCfg_t uartConfig;
    uartConfig.configured               = TRUE;
    uartConfig.baudRate                 = HAL_UART_BR_115200;
    uartConfig.flowControl              = FALSE;
    uartConfig.flowControlThreshold     = 0;
    uartConfig.rx.maxBufSize            = APP_UARTPORT_BUF_LEN;
    uartConfig.tx.maxBufSize            = 0;
    uartConfig.idleTimeout              = 5;
    uartConfig.intEnable                = TRUE;
    uartConfig.callBackFunc             = _uart_port_rx_callback;
    
    HalUARTOpen(HAL_UART_PORT_0, &uartConfig);
}

static void _uart_port_rx_callback(uint8 port, uint8 event)
{
    uint8 rx_len = Hal_UART_RxBufLen(HAL_UART_PORT_0);
    if(rx_len != 0)
    {
        HalUARTRead(HAL_UART_PORT_0, uart_port_rx_buf, rx_len);
        HalUARTWrite(HAL_UART_PORT_0, uart_port_rx_buf, rx_len);
    }
}



