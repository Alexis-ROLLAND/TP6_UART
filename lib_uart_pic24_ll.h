/**
 * @file Template_lib_std_H.h 
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	Template for PIC24 main app
 *  
 *
 */

//------------------------------------------------------------------------------
#ifndef	__LIB_UART_PIC24LL_H__
#define	__LIB_UART_PIC24LL_H__
#include <xc.h>

#ifndef	NULL
#define	NULL    (void*)0
#endif

#define UTX_BF_MASK (0x0001<<9)

typedef enum    {   _UART1,     /**< Value for UART1 */
                    _UART2}     /**< Value for UART2 */
                uart_id_t;
               
typedef enum    {UART_TX_NON_BLOCKING_MODE, UART_TX_BLOCKING_MODE} uart_tx_blocking_t;


/** Type uart_err_t
 * Liste les divers codes de retour des fonctions uart low level
 */
typedef enum    {   UART_OK,            /**< Succes value */
                    UART_ERROR,         /**< Non specific Error */
                    UART_UNKNOWN_UART,  /**< The UART ID is unknown  */
                    UART_TX_FIFO_FULL,  /**< TX_FIFO is full */
                    UART_BAD_PRIO      /**< Interrupt priority level outside the 0-7 range */
                } uart_err_t; 

 /** Type uart_config_t
 * Contient les valeurs à stocker dans les registres 
 * UxMODE, UxSTA et UxBRG pour un UART donné
  */
typedef struct{
    uint16_t    UxMODE; /**< UxMODE value */
    uint16_t    UxSTA;  /**< UxSTA value */
    uint16_t    UxBRG;  /**< UxBRG value */
    uint8_t     RxIrqPrio;    /**< Rx Interrupt priority level (between 0 and 7) */
}   uart_config_t;

 /** Type uart_desc_t
 * UART descritor type
 * 
 */
typedef struct{
    uart_id_t   uartID;
    uint8_t     RxIrqPrio;
    uint16_t    *pUxMODE;
    uint16_t    *pUxSTA;
    uint16_t    *pUxBRG;
    uint16_t    *pUxTXREG;
    uint16_t    *pUxRXREG;
    
}   uart_desc_t;




//------------------------------------------------------------------------------
/**
 * @brief   Configuration d'un UART  
 * 
 * @param[in]   uart_id
 * @param[in]   Adress of an uart_config_t variable (holding the desired configuration)  
 * @param[out]  Adress of an uart_desc_t variable (descriptor, set by the init function) 
 * 
 * @return      UART_OK on success, UART_UNKNOWN_UART otherwise 
 *
 */
uart_err_t  uart_init(uart_id_t uart_id, uart_config_t *pUartCFG, uart_desc_t *pUart);

//------------------------------------------------------------------------------
 /**
 * @brief  
 * 
 * @param[in]   Address of an initialized uart descriptor	
 * 
 * @return  UART_OK, UART_UNKNOWN_UART or UART_BAD_PRIO  
 *
 */
uart_err_t  uart_set_rx_interrupt(uart_desc_t *pUart);

//------------------------------------------------------------------------------
 /**
  * @brief  Send one character on a choosen UART 
  * 
  * @param[in]   Address of an initialized uart descriptor
  * @param[in]   Character to send
  * @param[in]   Send in blocking mode or non blocking mode 	
  *  
  * @return     UART_OK on success or UART_TX_FIFO_FULL in non blocking mode if Tx FIFO is full
  *
  */
uart_err_t      uart_putch(uart_desc_t *pUart, uint8_t Car, uart_tx_blocking_t BlockingMode);

//------------------------------------------------------------------------------ 
 /**
 * @brief  Sends a C Formatted string, blocking mode only
 * 
 * @param[in]   Address of an initialized uart descriptor
 * @param[in]   Address of the string to send	
 * 
 * @return   UART_OK
 *
 */
uart_err_t      uart_puts(uart_desc_t *pUart, uint8_t *pString);

//------------------------------------------------------------------------------
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */


//------------------------------------------------------------------------------
/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


#endif


