/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_mcu_ap6.h" // Inclusion du fichier .h "Applicatif" renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
uart_desc_t myUart;


/*	Implémentation du code */
//------------------------------------------------------------------------------
#ifdef  TEST_PUTCH
void Initialiser(void)
{
    uart_config_t   uart_cfg;
    
    uart_cfg.UxMODE = 0x8000;   // BRG Low Speed Mode
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = 25;    // 9600bps @Fcy=4MHz
    
    uart_init(USED_UART, &uart_cfg,&myUart);
}
#endif // !TEST_PUTCH
//------------------------------------------------------------------------------
#ifdef  TEST_PUTS
void Initialiser(void)
{
    uart_config_t   uart_cfg;
    
    uart_cfg.UxMODE = 0x8008;   // BRG High Speed Mode
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = 51;    // 19200bps @Fcy=4MHz 
    
    uart_init(USED_UART, &uart_cfg,&myUart);
}
#endif // !TEST_PUTS
//------------------------------------------------------------------------------
#ifdef TEST_RX_IRQ

uint8_t CarRec = 0;

void Initialiser(void)
{
    // PORTA[7:0] = GPIO Output (leds)
    TRISA &= 0xFF00;
    
    // UART Config
    uart_config_t   uart_cfg;
    
    uart_cfg.UxMODE = 0x8008;   // BRG High Speed Mode
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = 52;    // 19200bps @Fcy=4MHz /!\ 52 != 51 
    uart_cfg.RxIrqPrio = 4; // default value
    
    uart_init(USED_UART, &uart_cfg,&myUart);
    uart_set_rx_interrupt(&myUart);
}

/*
// ISR if UART1 is used
void _ISR __attribute__((no_auto_psv))  _U1RXInterrupt(void)
{ 
    CarRec = U1RXREG;
    IFS0bits.U1RXIF = 0;
}
*/

//*-----------------------------------------------------------------------------
// ISR if UART2 is used
void _ISR __attribute__((no_auto_psv))  _U2RXInterrupt(void)
{ 
    CarRec = U2RXREG;
    IFS1bits.U2RXIF = 0;
}
//------------------------------------------------------------------------------*/

#endif  // !TEST_RX_IRQ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

