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



/*	Implémentation du code */
#ifdef  TEST_PUTCH
void Initialiser(void)
{
    uart_config_t   uart_cfg;
    
    uart_cfg.UxMODE = 0x8000;   // BRG Low Speed Mode
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = 25;    // 9600bps @Fcy=4MHz
    
    uart_init(USED_UART, &uart_cfg);
}
#endif

#ifdef  TEST_PUTS
void Initialiser(void)
{
    uart_config_t   uart_cfg;
    
    uart_cfg.UxMODE = 0x8008;   // BRG High Speed Mode
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = 51;    // 19200bps @Fcy=4MHz 
    
    uart_init(USED_UART, &uart_cfg);
}
#endif



