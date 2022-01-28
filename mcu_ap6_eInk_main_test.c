/**
 * @file mcu_ap6_main_test.c 
 * @author 	Alexis ROLLAND
 * @date	01/2022
 * @brief 	
 *  
 *
 */

#include "lib_test_eInk.h"  
//------------------------------------------------------------------------------
/**
 * Insérer Ici les bits de configuration pour le MCU 						  
 * Copier / Coller depuis le fichier Config_Pic24.txt					  
 */
/*--------------------------------------------------------------------------*/
/* PIC24FJ128GA010															*/
/*--------------------------------------------------------------------------*/
#pragma config POSCMOD = HS         // Primary Oscillator Select (EC, XT, HS, NONE)
#pragma config OSCIOFNC = ON        // Primary Oscillator Output Function (ON, OFF)
#pragma config FCKSM = CSDCMD       // Clock Switching and Monitor (CSECME, CSECMD, CSDCMD)
#pragma config FNOSC = PRIPLL       // Oscillator Select (FRC, FRCPLL, PRI, PRIPLL, SOSC, LPRC, FRCDIV)
#pragma config IESO = OFF           // Internal External Switch Over Mode (ON, OFF)
#pragma config WDTPS = PS256        // Watchdog Timer Postscaler (PS1, PS2, PS4, PS8,..., PS32768)
#pragma config FWPSA = PR32         // WDT Prescaler (PR32, PR128)
#pragma config WINDIS = ON          // Watchdog Timer Window (ON, OFF)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (ON, OFF)
#pragma config ICS = PGx2           // Comm Channel Select (PGx1, PGx2)
#pragma config BKBUG = OFF          // Background Debug (ON, OFF)
#pragma config GWRP = OFF           // General Code Segment Write Protect (ON, OFF)
#pragma config GCP = OFF            // General Code Segment Code Protect (ON, OFF)
#pragma config JTAGEN = OFF         // JTAG Port Enable (ON, OFF)
//----------------------------------------------------------------------------

/* Directives de compilation - Macros		*/



/* Déclarations des variables globales 	*/
extern  eink_config_t   eink_cfg;

//------------------------------------------------------------------------------
#ifdef  TEST_DISPLAY
/* Programme Principal			*/
int main(void)
{
// Variables locales au main
eink_err_t  Res;
    
Initialiser();		// Appel fonction d'initialisation

__delay_ms(5000);
Res = eink_initiate_transfer(&eink_cfg);
if (Res != EINK_OK) error_handler();


while(1)
    {
    
    }
}					
#endif  // 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

