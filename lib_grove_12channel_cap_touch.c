/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_grove_12channel_cap_touch.h" 

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
const uint16_t  tabBRG[6]={25, 103, 207, 312, 416, 832};
const uint8_t   tabCar[13]={0,'1','2','3','4','5','6','7','8','9','*','0','#'};

uart_config_t   uart_cfg;

uint8_t RxCode;


/*	Implémentation du code */
//------------------------------------------------------------------------------
grove_12channel_touch_err_t grove_12channel_touch_init(grove_12channel_touch_config_t *pCfg)
{
    uart_err_t  Res;
    
    uart_cfg.UxMODE = 0x8008;   // High Speed BRG
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = tabBRG[pCfg->Fosc];
    uart_cfg.RxIrqPrio = 4;
    Res = uart_init(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return GROVE_12CHANNEL_TOUCH_ERROR;
    
    Res = uart_set_rx_interrupt(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return GROVE_12CHANNEL_TOUCH_ERROR;
    
    return GROVE_12CHANNEL_TOUCH_OK;
}

//------------------------------------------------------------------------------
grove_12channel_touch_err_t grove_12channel_touch_getData(uint8_t *pCar)
{
    if (RxCode == 0) return GROVE_12CHANNEL_TOUCH_NO_DATA;
    
    if ( (RxCode & 0xE0) != 0xE0 )
    {
        *pCar = 0x00;
        RxCode = 0;
        return GROVE_12CHANNEL_TOUCH_BAD_DATA;
    }
    
    RxCode &= 0x0F;
    if ((RxCode < 1) || (RxCode >= 0x0D))
    {
        *pCar = 0x00;
        RxCode = 0;
        return GROVE_12CHANNEL_TOUCH_BAD_DATA;
    }
    
    *pCar=tabCar[RxCode];
    RxCode = 0;
    return GROVE_12CHANNEL_TOUCH_OK;
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ISR Function (based on the GROVE_12_CH_TOUCH_ID_UART macro value (1 or 2)
#if (GROVE_12_CH_TOUCH_ID_UART == 1)
void _ISR __attribute__((no_auto_psv))  _U1RXInterrupt(void)
{
    RxCode = U1RXREG;
    IFS0bits.U1RXIF = 0;    // RxFlag
}
#endif

#if (GROVE_12_CH_TOUCH_ID_UART == 2)
void _ISR __attribute__((no_auto_psv))  _U2RXInterrupt(void)
{
    RxCode = U2RXREG;
    IFS1bits.U2RXIF = 0;    // RxFlag
}
#endif



//------------------------------------------------------------------------------
