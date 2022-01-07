/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_test_grove_12channel_cap_touch.h" // Inclusion du fichier .h "Applicatif" renomm�

/* Directives de compilation - Macros		*/


/* D�clarations des variables globales 	*/



/*	Impl�mentation du code */
void Initialiser(void)
{
    grove_12channel_touch_config_t g12ct_cfg;
    
    g12ct_cfg.Fosc=MHZ_8;
    g12ct_cfg.uart_id = _UART1;
    
    grove_12channel_touch_init(&g12ct_cfg);
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

