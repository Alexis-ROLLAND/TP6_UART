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

typedef enum    {   _UART1,     /**< Value for UART1 */
                    _UART2}     /**< Value for UART2 */
                uart_id_t;
               
/** Definition d'un type booléen bool_t
 * Version sécurisée par macro guard
 * */
#ifndef _BOOL_T_TYPE_
#define _BOOL_T_TYPE_                
typedef enum    {true, false} bool_t;
#endif

/** Type uart_err_t
 * Liste les divers codes de retour des fonctions uart low level
 */
typedef enum    {   UART_OK,            /**< Succes value */
                    UART_ERROR,         /**< Non specific Error */
                    UART_UNKNOWN_UART,  /**< The UART ID is unknown  */
                    UART_TX_FIFO_FULL}  /**< TX_FIFO is full */
                    uart_err_t; 

 /** Type uart_config_t
 * Contient les valeurs à stocker dans les registres 
 * UxMODE, UxSTA et UxBRG pour un UART donné
  */
typedef struct{
    uint16_t    UxMODE; /**< UxMODE value */
    uint16_t    UxSTA;  /**< UxSTA value */
    uint16_t    UxBRG;  /**< UxBRG value */
} uart_config_t;



/**
 * @brief   Configuration d'un UART  
 * 
 * @param[in]   uart_id
 * @param[in]   Adress of an uart_config_t variable (holding the desired configuration)  
 * 
 * @return      UART_OK on success, UART_UNKNOWN_UART otherwise 
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


