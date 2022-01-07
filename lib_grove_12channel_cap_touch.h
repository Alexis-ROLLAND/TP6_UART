/**
 * @file     
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */
#ifndef	__LIB_GROVE_12_CHANNEL_TOUCH_H__
#define	__LIB_GROVE_12_CHANNEL_TOUCH_H__

#include <xc.h>

#include "lib_uart_pic24_ll.h"


typedef enum {
            GROVE_12CHANNEL_TOUCH_OK,
            GROVE_12CHANNEL_TOUCH_ERROR,
            GROVE_12CHANNEL_TOUCH_FOSC_NOT_SUPPORTED,
            GROVE_12CHANNEL_TOUCH_NO_DATA,
            GROVE_12CHANNEL_TOUCH_BAD_DATA
            } grove_12channel_touch_err_t;

typedef enum {
                MHZ_2 = 0,      /**< 2MHz Osc (Fcy = 1e6) */
                MHZ_8 = 1,      /**< 8MHz Osc (Fcy = 4e6) */
                MHZ_16 = 2,     /**< 16MHz Osc (Fcy = 8e6) */
                MHZ_24 = 3,     /**< 24MHz Osc (Fcy = 12e6) */
                MHZ_32 = 4,     /**< 32MHz Osc (Fcy = 16e6) */
                MHZ_64 = 5      /**< 64MHz Osc (Fcy = 32e6) */
            } supported_fosc_t;

            
#define GROVE_12_CH_TOUCH_ID_UART   1   // 1 for UART1, 2 for UART2
typedef struct{
    uart_id_t uart_id;
    supported_fosc_t Fosc;
    } grove_12channel_touch_config_t; 


//------------------------------------------------------------------------------
/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 grove_12channel_touch_err_t grove_12channel_touch_init(grove_12channel_touch_config_t *pCfg);

 //------------------------------------------------------------------------------
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   OK or NO_DATA or BAD_DATA(prefixed)
 *
 */
 grove_12channel_touch_err_t grove_12channel_touch_getData(uint8_t *pCar);
 
 
//------------------------------------------------------------------------------
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 


#endif



