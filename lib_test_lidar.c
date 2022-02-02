/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_test_lidar.h"
#include "lib_lidar.h" // Inclusion du fichier .h "Applicatif" renomm�

/* Directives de compilation - Macros		*/


/* D�clarations des variables globales 	*/
extern lidar_config_t  lidar_cfg;


/*	Impl�mentation du code */
//------------------------------------------------------------------------------
#ifdef  TEST_RX
void Initialiser(void)
{
    
    
    lidar_cfg.Fosc = MHZ_32;
    lidar_cfg.uart_id = _UART1;
    
    lidar_init(&lidar_cfg);
    
    TRISA = 0xFF00;
}
#endif // !TEST_RX
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

