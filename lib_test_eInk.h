/**
 * @file     
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */
#ifndef	__LIB_TEST_EINK_H__
#define	__LIB_TEST_EINK_H__

//-----------------------------------------------------------------------------
#define TEST_DISPLAY
//-----------------------------------------------------------------------------

#ifndef FCY
#define FCY 16000000UL
#endif

#include <libpic30.h>
#include <xc.h>

#include "lib_eInk.h"


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
void    error_handler(void);

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



