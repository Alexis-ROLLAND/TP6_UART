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

uart_err_t      uart_putch(uart_id_t uart_id, uint8_t Car, bool_t BlockingMode)
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
                if (BlockingMode == false) return UART_TX_FIFO_FULL;    // Mode non bloquant, buffer plein, on retourne une erreur
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
                if (BlockingMode == false) return UART_TX_FIFO_FULL;    // Mode non bloquant, buffer plein, on retourne une erreur
                while (U2STAbits.UTXBF == 1);   // Attente libération buffer
                U2TXREG = Car;
            }
        default: 
            return UART_UNKNOWN_UART;
            break;
            
    }
    
    return UART_OK;
}

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

