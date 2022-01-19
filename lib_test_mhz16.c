/**
 * @file 
 * @author 	
 * @date	
 * @brief 	
 *  
 *
 */


#include "lib_test_mhz16.h"
#include "lib_mhz16.h"

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
mhz16_config_t  SensorCfg;

/*	Implémentation du code */
#ifdef  TEST_SEND_COMMAND
void Initialiser(void)
{
    
    SensorCfg.uart_id = USED_UART;
    SensorCfg.Fosc = MHZ_8;
    
    mhz16_init(&SensorCfg);  
    
    
    TRISA = 0xFF00;
}
#endif // 





