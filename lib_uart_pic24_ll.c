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



/*	Implémentation du code */
//------------------------------------------------------------------------------
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
    if (pUartCFG->RxIrqPrio > 7) return UART_BAD_PRIO;
    
    switch (uart_id)
    {
        case _UART1:
            IFS0bits.U1RXIF = 0;
            IPC2bits.U1RXIP = pUartCFG->RxIrqPrio;
            IEC0bits.U1RXIE = 1;
            break;
        case _UART2:
            IFS1bits.U2RXIF = 0;
            IPC7bits.U2RXIP = pUartCFG->RxIrqPrio;
            IEC1bits.U2RXIE = 1;
            break;
        default: 
            return UART_UNKNOWN_UART;
            break;
    }
    return UART_OK;
}

//------------------------------------------------------------------------------
uart_err_t      uart_putch(uart_id_t uart_id, uint8_t Car, uart_tx_blocking_t BlockingMode)
{
    switch (uart_id)
    {
        case _UART1:
            if (U1STAbits.UTXBF == 0)   // Si le buffer Tx est libre, on émet sans attendre, quelquesoit le mode (bloquant ou non)  
            {
                U1TXREG = Car;
                return UART_OK;
            }
            else
            {
                if (BlockingMode == UART_TX_NON_BLOCKING_MODE) return UART_TX_FIFO_FULL;    // Mode non bloquant, buffer plein, on retourne une erreur
                while (U1STAbits.UTXBF == 1);   // Attente libération buffer
                U1TXREG = Car;
            }
        
        case _UART2:
            if (U2STAbits.UTXBF == 0)   // Si le buffer Tx est libre, on émet sans attendre, quelquesoit le mode (bloquant ou non)  
            {
                U2TXREG = Car;
                return UART_OK;
            }
            else
            {
                if (BlockingMode == UART_TX_NON_BLOCKING_MODE) return UART_TX_FIFO_FULL;    // Mode non bloquant, buffer plein, on retourne une erreur
                while (U2STAbits.UTXBF == 1);   // Attente libération buffer
                U2TXREG = Car;
            }
        default: 
            return UART_UNKNOWN_UART;
            break;
            
    }
    
    return UART_OK;
}

//------------------------------------------------------------------------------
uart_err_t      uart_puts(uart_id_t uart_id, uint8_t *pString)
{
    switch (uart_id)
    {
        case _UART1:
            while(*pString != '\0'){
                while (U1STAbits.UTXBF == 1);   // Attente libération buffer
                U1TXREG = *pString;
                pString++;
            }
            break;
        case _UART2:
            while(*pString != '\0'){
                while (U2STAbits.UTXBF == 1);   // Attente libération buffer
                U2TXREG = *pString;
                pString++;
            }
            break;
        default: return UART_UNKNOWN_UART;
    }
    return UART_OK;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


