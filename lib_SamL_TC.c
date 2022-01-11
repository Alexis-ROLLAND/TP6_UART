/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	
 * @brief 	
 *  
 *
 */


#include "lib_SamL_TC.h" // Inclusion du fichier .h  renommé

/* Directives de compilation - Macros		*/
const uint16_t  tabBRG[6]={16, 25, 34, 69};

/* Déclarations des variables globales 	*/
uart_config_t   uart_cfg;

unsigned char   RxCar = 0;
unsigned char   RxBuffer[128];
unsigned char   RxPtr = 0;
tRxStatus       EtatRx = WAIT_START;
/*	Implémentation du code */
saml_touch_click_err_t  saml_touch_click_init(saml_touch_click_config_t *pCfg)
{
    uart_err_t  Res;
    
    uart_cfg.UxMODE = 0x8008;   // High Speed BRG
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = tabBRG[pCfg->Fosc];
    uart_cfg.RxIrqPrio = 4;
    
    Res = uart_init(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return SAML_TOUCH_CLICK_ERROR;
    
    Res = uart_set_rx_interrupt(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return SAML_TOUCH_CLICK_ERROR;
    return SAML_TOUCH_CLICK_OK;
}
//-----------------------------------------------------------------------------
saml_touch_click_err_t  saml_touch_click_check(void)
{
    if (EtatRx == WAIT_RD_BUFFER) return SAML_TOUCH_CLICK_DATA_AVAILABLE;
    else return SAML_TOUCH_CLICK_NO_DATA_AVAILABLE;
}
//-----------------------------------------------------------------------------
saml_touch_click_err_t  saml_touch_click_clear(void)
{
    EtatRx = WAIT_START;
    return SAML_TOUCH_CLICK_OK;
}
//-----------------------------------------------------------------------------
saml_touch_click_err_t  saml_touch_click_update(saml_touch_click_Status_t *pStatus)
{
    pStatus->Btn1 = RxBuffer[STC_INDEX_BTN1];
    pStatus->Btn2 = RxBuffer[STC_INDEX_BTN2];
    pStatus->SliderStatus = RxBuffer[STC_INDEX_SL_STATUS];
    pStatus->SliderValue = (((unsigned int)RxBuffer[STC_INDEX_SWH]) << 8 ) + RxBuffer[STC_INDEX_SWL];
    return SAML_TOUCH_CLICK_OK;
}
//-----------------------------------------------------------------------------
void _ISR __attribute__((no_auto_psv)) CLICKBOARD_RXISR(void)
{
    RxCar = CLICKBOARD_UXRXREG;
    
    switch(EtatRx)
    {
        case WAIT_START : 
            if (RxCar == STC_SOF)
            {
               RxPtr = 0;
               EtatRx = RX_ON;
            }
            break;
        case RX_ON:
            if (RxCar != STC_EOF)
            {
                RxBuffer[RxPtr] = RxCar;
                RxPtr++;
            }
            else
            {
                EtatRx = WAIT_RD_BUFFER;
            }
            break;
        case WAIT_RD_BUFFER:
            break;
        default: break;
            
    }
        
    RxCar = 0;
    
    CLICKBOARD_RXIF = 0;    
}
