/**
 * @file Template_lib_std_H.h 
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	Template for PIC24 main app
 *  
 *
 */

#ifndef	__LIB_SAML_TOUCH_CLICK_H__
#define	__LIB_SAML_TOUCH_CLICK_H__
#include <xc.h>

#include "lib_uart_pic24_ll.h"

typedef enum {
            SAML_TOUCH_CLICK_OK,
            SAML_TOUCH_CLICK_ERROR,
            SAML_TOUCH_CLICK_FOSC_NOT_SUPPORTED,
            SAML_TOUCH_CLICK_DATA_AVAILABLE,        
            SAML_TOUCH_CLICK_NO_DATA_AVAILABLE
            } saml_touch_click_err_t;

            
typedef enum {
                MHZ_16 = 0,     /**< 16MHz Osc (Fcy = 8e6) */
                MHZ_24 = 1,     /**< 24MHz Osc (Fcy = 12e6) */
                MHZ_32 = 2,     /**< 32MHz Osc (Fcy = 16e6) */
                MHZ_64 = 3      /**< 64MHz Osc (Fcy = 32e6) */
            } supported_fosc_t;
            
#define SAML_TOUCH_CLICK_UART   1
#if (SAML_TOUCH_CLICK_UART == 1)
    #define CLICKBOARD_BFBIT   U1STAbits.UTXBF
    #define CLICKBOARD_UXTXREG U1TXREG
    #define CLICKBOARD_RXIE    IEC0bits.U1RXIE 
    #define CLICKBOARD_RXISR   _U1RXInterrupt 
    #define CLICKBOARD_UXRXREG U1RXREG
    #define CLICKBOARD_RXIF    IFS0bits.U1RXIF  
#elif (SAML_TOUCH_CLICK_UART == 2)
    #define CLICKBOARD_BFBIT   U2STAbits.UTXBF
    #define CLICKBOARD_UXTXREG U2TXREG
    #define CLICKBOARD_RXIE    IEC1bits.U2RXIE 
    #define CLICKBOARD_RXISR   _U2RXInterrupt
    #define CLICKBOARD_UXRXREG U2RXREG
    #define CLICKBOARD_RXIF    IFS1bits.U2RXIF
#endif      
        
#define STC_SOF     0x55
#define STC_EOF     0xAA

#define STC_INDEX_BTN1       9
#define STC_INDEX_BTN2      19
#define STC_INDEX_SL_STATUS 61
#define STC_INDEX_SWL       66
#define STC_INDEX_SWH       65
            
#ifndef RX_STATUS_TYPE
#define RX_STATUS_TYPE
typedef enum    {WAIT_START,RX_ON,WAIT_RD_BUFFER} tRxStatus;
#endif

typedef struct{
    uart_id_t uart_id;
    supported_fosc_t Fosc;
    } saml_touch_click_config_t;

    
typedef struct {
    unsigned char   Btn1;
    unsigned char   Btn2;
    unsigned char   SliderStatus;
    unsigned int    SliderValue;    
    } saml_touch_click_Status_t;
/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
saml_touch_click_err_t  saml_touch_click_init(saml_touch_click_config_t *pCfg);

 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 saml_touch_click_err_t  saml_touch_click_check(void);
 

 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 saml_touch_click_err_t  saml_touch_click_clear(void);
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 saml_touch_click_err_t  saml_touch_click_update(saml_touch_click_Status_t *pStatus);
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 

#endif


