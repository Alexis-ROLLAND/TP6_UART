/**
 * @file     
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */
#ifndef	__LIB_MCU_AP6_H__
#define	__LIB_MCU_AP6_H__

//-----------------------------------------------------------------------------
//#define TEST_PUTCH
//#define TEST_PUTS
#define TEST_RX_IRQ
//-----------------------------------------------------------------------------

#ifndef FCY
#define FCY 4000000UL
#endif

#include <libpic30.h>
#include <xc.h>

#include "lib_uart_pic24_ll.h"


#define USED_UART _UART1


//------------------------------------------------------------------------------
/**
 * @brief Global init function/task 
 * 
 * @param	None
 * 
 * @return  Nothing 
 *
 */
void Initialiser(void);

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
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 


#endif



