/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	
 * @brief 	
 *  
 *
 */


#include "lib_lidar.h" // Inclusion du fichier .h  renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
const uint16_t  tabBRG[4]={16, 25, 34, 69}; // 115200bps

uart_config_t   uart_cfg;

lidar_rx_status_t   RxStatus = WAIT_STX1;
uint8_t         RxBuff[BUFF_SIZE];
uint8_t         RxCar = 0;
uint8_t         RxPtr = 0;
uint8_t         ChkSum;

lidar_err_t LastChk;

lidar_status_t  lidar_data;
/*	Implémentation du code */
lidar_err_t    lidar_init(lidar_config_t *pCfg)
{
    uart_err_t  Res;
    
    uart_cfg.UxMODE = 0x8008;   // High Speed BRG
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = tabBRG[pCfg->Fosc];
    uart_cfg.RxIrqPrio = 4;
    
    Res = uart_init(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return LIDAR_ERROR;
    
    Res = uart_set_rx_interrupt(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return LIDAR_ERROR;
    return LIDAR_OK;
}
//-----------------------------------------------------------------------------
lidar_err_t    lidar_get_data(lidar_config_t *pCfg, lidar_status_t *pData)
{
    pData->Distance = lidar_data.Distance;
    pData->Strength = lidar_data.Strength;
    pData->IntegTime = lidar_data.IntegTime;
    return LastChk;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _ISR __attribute__((no_auto_psv)) LIDAR_RXISR(void)
{
    RxCar = LIDAR_UXRXREG;
    switch(RxStatus)
    {
        case WAIT_STX1:
            if (RxCar == LIDAR_STX) RxStatus = WAIT_STX2;
            break;
        case WAIT_STX2:
            if (RxCar == LIDAR_STX)
            {
                RxPtr = 0;
                ChkSum = LIDAR_BASE_CHKSUM;
                RxStatus = RX_ON;
            }
            else
            {
                RxStatus = WAIT_STX1;
            }
            break;
        case RX_ON:
            if (RxPtr < BUFF_SIZE){
                RxBuff[RxPtr] = RxCar;
                ChkSum += RxCar;
                RxPtr++;
            }
            else
            {
                if (ChkSum == RxCar){
                    LastChk = LIDAR_LAST_CHK_OK;
                    
                    lidar_data.Distance = RxBuff[1];
                    lidar_data.Distance <<= 8;
                    lidar_data.Distance += RxBuff[0];
                    
                    lidar_data.Strength = RxBuff[3];
                    lidar_data.Strength <<= 8;
                    lidar_data.Strength += RxBuff[2];
                    
                    lidar_data.IntegTime = RxBuff[4];
                    
                    RxStatus = WAIT_STX1;
                }
                else
                {
                    LastChk = LIDAR_LAST_CHK_ERROR;
                    lidar_data.Distance = 0;
                    lidar_data.Strength = 0;
                    lidar_data.IntegTime = 0;
                    
                    RxStatus = WAIT_STX1;
                }
                
            }
            
            
    }
    
    LIDAR_RXIF = 0;   
}
//-----------------------------------------------------------------------------
