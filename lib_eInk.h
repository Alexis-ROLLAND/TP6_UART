/**
 * @file     
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */
#ifndef	__LIB_EINK_H__
#define	__LIB_EINK_H__

#ifndef FCY
#define FCY 16000000UL
#endif

#include <libpic30.h>
#include <xc.h>

#include "lib_uart_pic24_ll.h"

#define     EINK_STX            'a'
#define     EINK_READY          0x0A
#define     EINK_RX_DELAY_MS    10
#define     NB_TIMEOUT          500
#define     EINK_TX_DELAY_MS    70
#define     EINK_BULK_SIZE      76

typedef enum{
            EINK_OK,
            EINK_TIME_OUT,
            EINK_ERROR
            } eink_err_t;

typedef enum{
            MHZ_32 = 0,     /**< 32MHz Osc (Fcy = 16e6) */
            MHZ_64 = 1      /**< 64MHz Osc (Fcy = 32e6) */
            } supported_fosc_t;

#define EINK_UART   1
#if (EINK_UART == 1)
    #define EINK_BFBIT   U1STAbits.UTXBF
    #define EINK_UXTXREG U1TXREG
    #define EINK_RXIE    IEC0bits.U1RXIE 
    #define EINK_RXISR   _U1RXInterrupt 
    #define EINK_UXRXREG U1RXREG
    #define EINK_RXIF    IFS0bits.U1RXIF  
#elif (EINK_UART == 2)
    #define EINK_BFBIT   U2STAbits.UTXBF
    #define EINK_UXTXREG U2TXREG
    #define EINK_RXIE    IEC1bits.U2RXIE 
    #define EINK_RXISR   _U2RXInterrupt
    #define EINK_UXRXREG U2RXREG
    #define EINK_RXIF    IFS1bits.U2RXIF
#endif 

typedef struct{
        uart_id_t uart_id;
        supported_fosc_t Fosc;
        } eink_config_t;
    
    
//------------------------------------------------------------------------------
/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
eink_err_t eink_init(eink_config_t *pCfg);


 //------------------------------------------------------------------------------
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 eink_err_t eink_initiate_transfer(eink_config_t *pCfg);


//------------------------------------------------------------------------------
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 eink_err_t eink_send_image(eink_config_t *pCfg, uint8_t *pBlack, uint8_t *pRed);
 
 //------------------------------------------------------------------------------
 /**
 * @brief  Low Level Function
 * 
 * @param	
 * 
 * @return   
 *
 */
 eink_err_t eink_send_bulk(eink_config_t *pCfg, uint8_t *pBulk, uint8_t size);


#endif



