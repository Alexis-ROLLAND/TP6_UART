/**
 * @file Template_lib_std_H.h 
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	Template for PIC24 main app
 *  
 *
 */


#ifndef	__LIB_UART_PIC24LL_H__
#define	__LIB_UART_PIC24LL_H__
#include <xc.h>

typedef enum    {_UART1, _UART2} uart_id_t;
typedef enum    {true, false} bool_t;
typedef enum    {UART_OK, UART_ERROR, UART_TX_FIFO_FULL} uart_err_t; 

typedef struct{
    uint16_t    UxMODE;
    uint16_t    UxSTA;
    uint16_t    UxBRG;
} uart_config_t;



/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
uart_err_t  uart_init(uart_id_t uart_id, uart_config_t *pUartCFG);

 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
uart_err_t      uart_putch(uart_id_t uart_id, uint8_t Car, bool_t BlockingMode);

 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 

#endif


