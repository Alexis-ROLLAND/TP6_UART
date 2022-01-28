/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */


#include "lib_eInk.h"


/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
const uint16_t  tabBRG[2]={16,32};
uart_config_t   uart_cfg;
uint8_t         RxCar = 0;

/*	Implémentation du code */


//------------------------------------------------------------------------------
eink_err_t eink_init(eink_config_t *pCfg)
{
    uart_err_t  Res;
    
    uart_cfg.UxMODE = 0x8008;   // High Speed BRG
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = tabBRG[pCfg->Fosc];
    uart_cfg.RxIrqPrio = 4;
    
    Res = uart_init(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return EINK_ERROR;
    
    Res = uart_set_rx_interrupt(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return EINK_ERROR;
    
    return EINK_OK;
}
//------------------------------------------------------------------------------
eink_err_t eink_initiate_transfer(eink_config_t *pCfg)
{
    uint16_t NbRx = 0;
    uart_putch(pCfg->uart_id, EINK_STX, UART_TX_BLOCKING_MODE);
    
    do{
        if (RxCar ==  EINK_READY) return EINK_OK;
        
        if (RxCar != 0) RxCar = 0;
               
        NbRx++;
        __delay_ms(EINK_RX_DELAY_MS);
    } while (NbRx < NB_TIMEOUT);
    
    
    return EINK_TIME_OUT;
}
//------------------------------------------------------------------------------
eink_err_t eink_send_image(eink_config_t *pCfg, uint8_t *pBlack, uint8_t *pRed)
{
    uint8_t i;
    
    // Send black array
    for (i=0; i<38; i++)
    {
        eink_send_bulk(pCfg, &pBlack[i*EINK_BULK_SIZE], EINK_BULK_SIZE);
        __delay_ms(EINK_TX_DELAY_MS);
    }
     __delay_ms(EINK_TX_DELAY_MS);
     // Send red array
    for (i=0; i<38; i++)
    {
        eink_send_bulk(pCfg, &pRed[i*EINK_BULK_SIZE], EINK_BULK_SIZE);
        __delay_ms(EINK_TX_DELAY_MS);
    }
    
    return EINK_OK;
}
//------------------------------------------------------------------------------
eink_err_t eink_send_bulk(eink_config_t *pCfg, uint8_t *pBulk, uint8_t size)
{
    uint8_t i;
    
    for (i=0;i<size;i++) uart_putch(pCfg->uart_id, pBulk[i], UART_TX_BLOCKING_MODE);
        
    
    return EINK_OK;
}
//------------------------------------------------------------------------------
void _ISR __attribute__((no_auto_psv)) EINK_RXISR(void)
{
    RxCar = EINK_UXRXREG;
    
    EINK_RXIF = 0;   
}    
//------------------------------------------------------------------------------