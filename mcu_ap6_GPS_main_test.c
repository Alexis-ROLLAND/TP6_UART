/**
 * @file mcu_ap6_main_test.c 
 * @author 	Alexis ROLLAND
 * @date	
 * @brief 	
 *  
 *
 */

#include "lib_test_gps.h"   // Inclusion du fichier .h "Applicatif" renommé
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
#pragma config FNOSC = PRI          // Oscillator Select (FRC, FRCPLL, PRI, PRIPLL, SOSC, LPRC, FRCDIV)
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


//------------------------------------------------------------------------------
#ifdef  TEST_RX_GPS1
/* Programme Principal			*/
tRMC_MINIMAL_DATA Data;
int main(void)
{
// Variables locales au main
uint16_t    Nb = 0;    
    


Initialiser();		// Appel fonction d'initialisation

while(1)
    {
    if (gps_check() == GPS_PENDING_FRAME)
    {
        
        if (gps_decode(&Data) == GPS_OK)
        {
            Nb++;
            LATA++;
        }
        gps_clear();
    }
    
    
    }
}					
#endif  // !TEST_PUTCH
//------------------------------------------------------------------------------
