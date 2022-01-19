/**
 * @file Template_lib_std_C.c 
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	Template for PIC24 main app
 *  
 *
 */


#include "lib_mhz16.h" // Inclusion du fichier .h  renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
const uint16_t  tabBRG[6]={25, 103, 207, 312, 416, 832};

const uint8_t   mhz16_cmd_read_gas_concentration[9] = { MHZ16_SOF,
                                                        MHZ16_SENSOR_ID,
                                                        MHZ16_CMD_READ_SENSOR,
                                                        0x00,0x00,0x00,0x00,0x00,
                                                        MHZ16_CHECK_CMD_READ_SENSOR};

uart_config_t   uart_cfg;

/*	Implémentation du code */
//-----------------------------------------------------------------------------
mhz16_err_t   mhz16_init(mhz16_config_t *pCfg)
{
    mhz16_err_t  Res;
    
    uart_cfg.UxMODE = 0x8008;   // High Speed BRG
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = tabBRG[pCfg->Fosc];
    uart_cfg.RxIrqPrio = 4;
    
    Res = uart_init(pCfg->uart_id, &uart_cfg);
    if (Res != MHZ16_OK) return MHZ16_ERROR;
    
    /*
    Res = uart_set_rx_interrupt(pCfg->uart_id, &uart_cfg);
    if (Res != MHZ16_OK) return MHZ16_ERROR;
    */
    
    return MHZ16_OK;   
}
//-----------------------------------------------------------------------------
mhz16_err_t   mhz16_send_cmd(mhz16_config_t *pCfg,const uint8_t *pCmd)
{   uint8_t i;
        
    for (i=0; i<MHZ16_CMD_FRAME_SIZE; i++)
    {
        uart_putch(pCfg->uart_id, pCmd[i], UART_TX_BLOCKING_MODE);
    }
    return MHZ16_OK;
}
//-----------------------------------------------------------------------------
mhz16_err_t   mhz16_start_read_gas_concentration(mhz16_config_t *pCfg)
{
    return mhz16_send_cmd(pCfg, mhz16_cmd_read_gas_concentration);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------






