/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */

#ifndef	__LIB_GPS_H__
#define	__LIB_GPS_H__
#include <xc.h>
#include <string.h>

#include "lib_uart_pic24_ll.h"

#define GPS_UART   1
#if (GPS_UART == 1)
    #define GPS_BFBIT   U1STAbits.UTXBF
    #define GPS_UXTXREG U1TXREG
    #define GPS_RXIE    IEC0bits.U1RXIE 
    #define GPS_RXISR   _U1RXInterrupt 
    #define GPS_UXRXREG U1RXREG
    #define GPS_RXIF    IFS0bits.U1RXIF  
#elif (GPS_UART == 2)
    #define GPS_BFBIT   U2STAbits.UTXBF
    #define GPS_UXTXREG U2TXREG
    #define GPS_RXIE    IEC1bits.U2RXIE 
    #define GPS_RXISR   _U2RXInterrupt
    #define GPS_UXRXREG U2RXREG
    #define GPS_RXIF    IFS1bits.U2RXIF
#endif   

// différentes signatures selon module GPS pour la trame RMC 
//#define RMC_FRAME   "GPRMC,"
#define RMC_FRAME   "GNRMC,"

typedef enum {
                GPS_OK,
                GPS_NO_PENDING_FRAME,
                GPS_PENDING_FRAME,
                GPS_RECEIVE_ON,
                GPS_RECEIVE_OFF,        
                GPS_ERROR} gps_err_t;
                        
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
    } gps_config_t;
    
#ifndef RX_STATUS_TYPE
#define RX_STATUS_TYPE
typedef enum    {WAIT_START,RX_ON,WAIT_RD_BUFFER} RxStatus_t;
#endif

typedef enum    {GPS_RECEIVE_STATUS_OFF,GPS_RECEIVE_STATUS_ON} GpsReceiveStatus_t;

typedef struct{
    // UTC date of the fix
    uint8_t   day; // Day of the month[0 -> 31]
    uint8_t   month; //  Month [1 -> 12]
    uint8_t   year; //  Year [00 -> 99] (2000 -> 2099)
    
    // UTC time of the fix
    uint8_t   hh; //  UTC Hours [0 -> 23]
    uint8_t   mm; //  UTC Minutes [0 -> 59]
    uint8_t   ss; //  UTC seconds [0 -> 59]
    
    // Latitude
    uint8_t   latDeg; // Latitude degrees
    uint8_t   latMin; // Latitude minutes
    uint16_t  latDec; // decimal part of minutes
    uint8_t   latNS;  // either 'N' = North or 'S' = South
    
    // Longitude
    uint8_t   longDeg; // Latitude degrees
    uint8_t   longMin; // Latitude minutes
    uint16_t  longDec; // decimal part of minutes
    uint8_t   longEW;  // either  either 'E' = East or 'W' = West
    
    // Validité données
    uint8_t   ValidData;  // either 'A' = Valid or 'V' not valid
    
} tRMC_MINIMAL_DATA;

#define NMEA_START  '$'
#define NMEA_CR     0x0D   // first car of the <CR><LF> sequence

#define NB_CHAMPS       15
#define TAILLE_CHAMP    16


/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
gps_err_t   gps_init(gps_config_t *pCfg);  
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
void    gps_receive_on(void);
void    gps_receive_off(void);
gps_err_t   gps_get_receive_status(void);

 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
gps_err_t    gps_check(void);

/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
void            gps_clear(void);
 

/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
gps_err_t       gps_decode(tRMC_MINIMAL_DATA *pData);


/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
int8_t          get2digits(uint8_t* pBuffer);
int16_t         get3digits(uint8_t* pBuffer);
int16_t         get4digits(uint8_t* pBuffer); 

/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
int8_t  SplitTrame(uint8_t * pBuffer);




#endif


