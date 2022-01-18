/**
 * @file 
 * @author 	Alexis ROLLAND
 * @date	2022
 * @brief 	
 *  
 *
 */

#include "lib_gps.h" // Inclusion du fichier .h  renommé


/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
const uint16_t  tabBRG[6]={25, 103, 207, 312, 416, 832};

uart_config_t   uart_cfg;

uint8_t   gpsRxBuffer[100]="";
uint8_t   gpsRxCar = 0;
uint8_t   gpsRxPtr = 0;
RxStatus_t       gpsEtatRx = WAIT_START;

uint8_t   Trame[NB_CHAMPS][TAILLE_CHAMP];

GpsReceiveStatus_t   GpsReceiveStatus = GPS_RECEIVE_STATUS_ON;

/*	Implémentation du code */
//-----------------------------------------------------------------------------
gps_err_t   gps_init(gps_config_t *pCfg)
{
    uart_err_t  Res;
    
    uart_cfg.UxMODE = 0x8008;   // High Speed BRG
    uart_cfg.UxSTA = 0x0400;
    uart_cfg.UxBRG = tabBRG[pCfg->Fosc];
    uart_cfg.RxIrqPrio = 4;
    Res = uart_init(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return GPS_ERROR;
    
    Res = uart_set_rx_interrupt(pCfg->uart_id, &uart_cfg);
    if (Res != UART_OK) return GPS_ERROR;
    
    return GPS_OK;
}
//-----------------------------------------------------------------------------
void    gps_receive_on(void)
{
    gpsRxPtr = 0;   // Raz rx pointer
    gpsEtatRx = WAIT_START;
    GpsReceiveStatus = GPS_RECEIVE_STATUS_ON;
    GPS_RXIE = 1;   // Autorisation IRQ Rx UART GPS
}
//----------------------------------------------------------------------------
void    gps_receive_off(void)
{
    GPS_RXIE = 0;   // Interdiction IRQ Rx UART GPS
    GpsReceiveStatus = GPS_RECEIVE_STATUS_OFF;
}
//----------------------------------------------------------------------------
gps_err_t   gps_get_receive_status(void)
{
    if (GpsReceiveStatus == GPS_RECEIVE_STATUS_ON) return GPS_RECEIVE_ON;
    else return GPS_RECEIVE_OFF;
    
}
//----------------------------------------------------------------------------
gps_err_t    gps_check(void)
{
        if (gpsEtatRx == WAIT_RD_BUFFER) return GPS_PENDING_FRAME; 
        else return GPS_NO_PENDING_FRAME;    
}
//----------------------------------------------------------------------------
void            gps_clear(void)
{
    gpsEtatRx = WAIT_START;    
}
//----------------------------------------------------------------------------
gps_err_t   gps_decode(tRMC_MINIMAL_DATA *pData)
{
    gps_err_t   Res;
    
    if (gpsEtatRx != WAIT_RD_BUFFER) return GPS_ERROR;
    
    if (strncmp((char*)gpsRxBuffer,RMC_FRAME,6) == 0)
    {
        SplitTrame(gpsRxBuffer);
        // Décodage Heure : champ 1 [HHMMSS.xxx]
        pData->hh = get2digits(Trame[1]);
        pData->mm = get2digits(Trame[1]+2);
        pData->ss = get2digits(Trame[1]+4);
        // Décodage date : champ 9 [DDMMYY]
        pData->day = get2digits(Trame[9]);
        pData->month = get2digits(Trame[9]+2);
        pData->year = get2digits(Trame[9]+4);
        // Décodage latitude : champ 3 [ddmm.____] + champ 4 : N/S
        pData->latDeg = get2digits(Trame[3]);
        pData->latMin = get2digits(Trame[3]+2);
        pData->latDec = get4digits(Trame[3]+5);
        pData->latNS = Trame[4][0];
        // Décodage longiture : champ 5 [dddmm.____] + champ 6 : O/E
        pData->longDeg = get3digits(Trame[5]);
        pData->longMin = get2digits(Trame[5]+3);
        pData->longDec = get4digits(Trame[5]+6);
        pData->longEW = Trame[6][0];
        
        pData->ValidData = Trame[2][0];
        
        Res = GPS_OK;
    }
    else
    {
        Res = GPS_ERROR;
    }
    return Res;
}
//-----------------------------------------------------------------------------
int8_t  SplitTrame(uint8_t * pBuffer)
{
    int8_t NbChamps = 0;
    char *Pointer;
    
    Pointer = strtok((char*)pBuffer, ",");
    while (Pointer != NULL)
        {
        strcpy((char*)Trame[NbChamps],Pointer);
        NbChamps++;
        Pointer = strtok(NULL, ","); 
        }
    return NbChamps;
}
//-----------------------------------------------------------------------------
int8_t          get2digits(uint8_t* pBuffer)
{
    int8_t Res; 
    
    if ((pBuffer[0] < '0') || (pBuffer[0] > '9')) return -1;
    if ((pBuffer[1] < '0') || (pBuffer[1] > '9')) return -1;
    
    Res = ((pBuffer[0]-0x30)* 10) + (pBuffer[1]-0x30);
    return Res;
}
//-----------------------------------------------------------------------------
int16_t         get3digits(uint8_t* pBuffer)
{
    int16_t Res; 
    
    if ((pBuffer[0] < '0') || (pBuffer[0] > '9')) return -1;
    if ((pBuffer[1] < '0') || (pBuffer[1] > '9')) return -1;
    if ((pBuffer[2] < '0') || (pBuffer[2] > '9')) return -1;
      
    Res = ((pBuffer[0]-0x30) * 100) + ((pBuffer[1]-0x30) * 10) + (pBuffer[2]-0x30);
    return Res;
}
//-----------------------------------------------------------------------------
int16_t         get4digits(uint8_t* pBuffer)
{
    int16_t Res; 
    
    if ((pBuffer[0] < '0') || (pBuffer[0] > '9')) return -1;
    if ((pBuffer[1] < '0') || (pBuffer[1] > '9')) return -1;
    if ((pBuffer[2] < '0') || (pBuffer[2] > '9')) return -1;
    if ((pBuffer[3] < '0') || (pBuffer[3] > '9')) return -1;
   
    Res = ((pBuffer[0]-0x30) * 1000) + ((pBuffer[1]-0x30) * 100) + ((pBuffer[2]-0x30) * 10) + (pBuffer[3]-0x30);
    return Res;
}

//-----------------------------------------------------------------------------
void _ISR __attribute__((no_auto_psv)) GPS_RXISR(void)
{
    gpsRxCar = GPS_UXRXREG;
    switch(gpsEtatRx)
    {
        case WAIT_START : 
            if (gpsRxCar == NMEA_START)
            {
               gpsRxPtr = 0;
               gpsEtatRx = RX_ON;
            }
            break;
        case RX_ON:
            if (gpsRxCar != NMEA_CR)
            {
                gpsRxBuffer[gpsRxPtr] = gpsRxCar;
                gpsRxPtr++;
            }
            else
            {
                gpsEtatRx = WAIT_RD_BUFFER;
            }
            break;
        case WAIT_RD_BUFFER:
            break;
        default: break;
            
    }
    
    GPS_RXIF = 0;  
}
//-----------------------------------------------------------------------------