/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_uart_pic24_ll.h" // Inclusion du fichier .h  renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/


//------------------------------------------------------------------------------
/*	Implémentation du code */
uart_err_t  uart_init(uart_id_t uart_id, uart_config_t *pUartCFG)
{
    switch (uart_id)
    {
        case _UART1:
            U1MODE = pUartCFG->UxMODE;
            U1STA = pUartCFG->UxSTA;
            U1BRG = pUartCFG->UxBRG;
            break;
        case _UART2:
            U2MODE = pUartCFG->UxMODE;
            U2STA = pUartCFG->UxSTA;
            U2BRG = pUartCFG->UxBRG;
            break;
        default: 
            return UART_UNKNOWN_UART;
            break;
    }
    return UART_OK;
}
//------------------------------------------------------------------------------
uart_err_t  uart_set_rx_interrupt(uart_id_t uart_id,uart_config_t *pUartCFG)
{
    
    
    
    return UART_OK;
}
//------------------------------------------------------------------------------
uart_err_t      uart_putch(uart_id_t uart_id, uint8_t Car, bool_t BlockingMode)
{
    
    
    return UART_OK;
}
//------------------------------------------------------------------------------
uart_err_t      uart_puts(uart_id_t uart_id, uint8_t *pString)
{
    
    
    return UART_OK;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

