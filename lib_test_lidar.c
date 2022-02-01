/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_test_lidar.h" // Inclusion du fichier .h "Applicatif" renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/



/*	Implémentation du code */
//------------------------------------------------------------------------------
#ifdef  TEST_RX
void Initialiser(void)
{
    uart_config_t   uart_cfg;
    
    uart_cfg.UxMODE = 0x8000;   // BRG Low Speed Mode
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = 25;    // 9600bps @Fcy=4MHz
    
    uart_init(USED_UART, &uart_cfg);
}
#endif // !TEST_RX
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

