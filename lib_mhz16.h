/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */

#ifndef	__LIB_MHZ16_H__
#define	__LIB_MHZ16_H__
#include <xc.h>

#include "lib_uart_pic24_ll.h"

#define MHZ16_UART   1
#if (MHZ16_UART == 1)
    #define GPS_RXIE    IEC0bits.U1RXIE 
    #define GPS_RXISR   _U1RXInterrupt 
    #define GPS_UXRXREG U1RXREG
    #define GPS_RXIF    IFS0bits.U1RXIF  
#elif (MHZ16_UART == 2)
    #define GPS_RXIE    IEC1bits.U2RXIE 
    #define GPS_RXISR   _U2RXInterrupt
    #define GPS_UXRXREG U2RXREG
    #define GPS_RXIF    IFS1bits.U2RXIF
#endif   

//-----------------------------------------------------------------------------
#define MHZ16_CMD_FRAME_SIZE            9

#define MHZ16_SOF                       0xFF
#define MHZ16_SENSOR_ID                 0x01
#define MHZ16_CMD_READ_SENSOR           0x86
#define MHZ16_CHECK_CMD_READ_SENSOR     0x79
//-----------------------------------------------------------------------------

typedef enum{
            MHZ16_OK,
            MHZ16_ERROR} mhz16_err_t;

typedef enum {
                MHZ_2 = 0,      /**< 2MHz Osc (Fcy = 1e6) */
                MHZ_8 = 1,      /**< 8MHz Osc (Fcy = 4e6) */
                MHZ_16 = 2,     /**< 16MHz Osc (Fcy = 8e6) */
                MHZ_24 = 3,     /**< 24MHz Osc (Fcy = 12e6) */
                MHZ_32 = 4,     /**< 32MHz Osc (Fcy = 16e6) */
                MHZ_64 = 5      /**< 64MHz Osc (Fcy = 32e6) */
            } supported_fosc_t;
            
typedef struct{
    uart_id_t uart_id;
    supported_fosc_t Fosc;
    } mhz16_config_t;            

/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
mhz16_err_t   mhz16_init(mhz16_config_t *pCfg);  

/**
 * @brief   low_level function
 * 
 * @param	
 * 
 * @return   
 *
 */
 mhz16_err_t   mhz16_send_cmd(mhz16_config_t *pCfg,const uint8_t *pCmd);
 
 /**
 * @brief   High Level function
 * 
 * @param	
 * 
 * @return   
 *
 */
 mhz16_err_t   mhz16_start_read_gas_concentration(mhz16_config_t *pCfg);
 
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 

#endif

