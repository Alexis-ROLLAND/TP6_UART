/**
 * @file Template_lib_std_H.h 
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	Template for PIC24 main app
 *  
 *
 */

#ifndef	__LIB_LIDAR_H__
#define	__LIB_LIDAR_H__
#include <xc.h>

#include "lib_uart_pic24_ll.h"

typedef enum {
            LIDAR_OK,
            LIDAR_ERROR,
            LIDAR_FOSC_NOT_SUPPORTED,
            LIDAR_CHECKSUM_ERROR,
            LIDAR_LAST_CHK_OK,
            LIDAR_LAST_CHK_ERROR
            } lidar_err_t;
            
            
typedef enum {
                MHZ_16 = 0,     /**< 16MHz Osc (Fcy = 8e6) */
                MHZ_24 = 1,     /**< 24MHz Osc (Fcy = 12e6) */
                MHZ_32 = 2,     /**< 32MHz Osc (Fcy = 16e6) */
                MHZ_64 = 3      /**< 64MHz Osc (Fcy = 32e6) */
            } supported_fosc_t;
            
#define LIDAR_UART   1
#if (LIDAR_UART == 1)
    #define LIDAR_BFBIT   U1STAbits.UTXBF
    #define LIDAR_UXTXREG U1TXREG
    #define LIDAR_RXIE    IEC0bits.U1RXIE 
    #define LIDAR_RXISR   _U1RXInterrupt 
    #define LIDAR_UXRXREG U1RXREG
    #define LIDAR_RXIF    IFS0bits.U1RXIF  
#elif (LIDAR_UART == 2)
    #define LIDAR_BFBIT   U2STAbits.UTXBF
    #define LIDAR_UXTXREG U2TXREG
    #define LIDAR_RXIE    IEC1bits.U2RXIE 
    #define LIDAR_RXISR   _U2RXInterrupt
    #define LIDAR_UXRXREG U2RXREG
    #define LIDAR_RXIF    IFS1bits.U2RXIF
#endif    

#define BUFF_SIZE           6
#define LIDAR_STX           0x59  
#define LIDAR_BASE_CHKSUM   0xB2    // Base checksum is 2 x 0x59 

typedef enum {WAIT_STX1, WAIT_STX2, RX_ON} lidar_rx_status_t;   
            
typedef struct{
    uart_id_t uart_id;
    supported_fosc_t Fosc;
    } lidar_config_t;     
   
    
typedef struct{
        uint16_t    Distance;
        uint16_t    Strength;
        uint8_t     IntegTime;
        
    } lidar_status_t;
    
    
/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 lidar_err_t    lidar_init(lidar_config_t *pCfg);
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 

#endif


