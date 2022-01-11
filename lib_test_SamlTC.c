/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_test_SamlTC.h" // Inclusion du fichier .h "Applicatif" renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/



/*	Implémentation du code */
//------------------------------------------------------------------------------

void Initialiser(void)
{
    saml_touch_click_config_t saml_cfg;
    
    saml_cfg.Fosc = MHZ_32;
    saml_cfg.uart_id = _UART1;
    
    saml_touch_click_init(&saml_cfg);
    
    TRISA = 0xFF00;
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

