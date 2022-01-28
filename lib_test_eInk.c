/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_test_eInk.h" // Inclusion du fichier .h "Applicatif" renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
eink_config_t   eink_cfg;


/*	Implémentation du code */
//------------------------------------------------------------------------------

void Initialiser(void)
{
    
    
    eink_cfg.Fosc = MHZ_32;
    eink_cfg.uart_id = _UART1;
    
    eink_init(&eink_cfg);
    
    TRISA = 0xFF00;
}

//------------------------------------------------------------------------------
void    error_handler(void)
{
    while(1)
    {
        LATAbits.LATA0 = ~LATAbits.LATA0;
        __delay_ms(75);
    }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

