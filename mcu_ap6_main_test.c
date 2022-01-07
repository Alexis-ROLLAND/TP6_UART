/**
 * @file mcu_ap6_main_test.c 
 * @author 	Alexis ROLLAND
 * @date	
 * @brief 	
 *  
 *
 */

#include "lib_mcu_ap6.h"   // Inclusion du fichier .h "Applicatif" renommé
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
#ifdef  TEST_PUTCH
/* Programme Principal			*/
int main(void)
{
// Variables locales au main
    uint8_t Car;
    


Initialiser();		// Appel fonction d'initialisation

while(1)
    {
    for (Car = 'A';Car <= 'Z';Car++){
        uart_putch(USED_UART, Car, true);
        __delay_ms(500);
    }
    }
}					
#endif  // !TEST_PUTCH
//------------------------------------------------------------------------------
#ifdef  TEST_PUTS
/* Programme Principal			*/
int main(void)
{
// Variables locales au main
    
Initialiser();		// Appel fonction d'initialisation

while(1)
    {
    uart_puts(USED_UART,(uint8_t*)"Hello World\n");
    
    __delay_ms(500);
    
    }
}					

#endif  // !TEST_PUTS
//------------------------------------------------------------------------------
#ifdef TEST_RX_IRQ
/* Programme Principal			*/
extern uint8_t  CarRec;
int main(void)
{
// Variables locales au main
    
Initialiser();		// Appel fonction d'initialisation

// For checking, at startup LEDs should display 0x55
LATA = 0x55;

while(1)
    {
    if (CarRec != 0){
        LATA = CarRec;
        CarRec = 0;
    }
    }
}					
#endif  // !TEST_RX_IRQ
//------------------------------------------------------------------------------

