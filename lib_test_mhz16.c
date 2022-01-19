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


/* D�clarations des variables globales 	*/
mhz16_config_t  SensorCfg;

/*	Impl�mentation du code */
#ifdef  TEST_SEND_COMMAND
void Initialiser(void)
{
    
    SensorCfg.uart_id = USED_UART;
    SensorCfg.Fosc = MHZ_8;
    
    mhz16_init(&SensorCfg);  
    
    
    TRISA = 0xFF00;
}
#endif // 





