/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_test_gps.h"  

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/



/*	Implémentation du code */
//------------------------------------------------------------------------------
#ifdef  TEST_RX_GPS1
void Initialiser(void)
{
    gps_config_t   gps_cfg;
    
    gps_cfg.Fosc = MHZ_8;
    gps_cfg.uart_id = _UART1;
    
    gps_init(&gps_cfg);
    
    TRISA = 0xFF00;
    LATA = 0;
    
}
#endif // !TEST_PUTCH
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

