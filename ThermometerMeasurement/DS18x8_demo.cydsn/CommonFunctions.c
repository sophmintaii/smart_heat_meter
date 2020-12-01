/****************************************************************************
* File Name: CommonFunctions.c
*
* Description:
* This file implements the common functions used by the application.
*
*****************************************************************************/


/*****************************************************************************
* Included headers
*****************************************************************************/
#include "CommonFunctions.h"
#include "BLE_HTSS.h"
#include "Temperature.h"

/* System Flag used to indicate system status */
uint32 SystemFlag = 0;


/*****************************************************************************
* Function Name: InitializeSystem()
******************************************************************************
* Summary:
* Initializes the complete system resources. 
*
* Parameters:
* None
*
* Return:
* None
*
* Theory:
* Initializes the system resources - enables BLE, starts UART and OneWire
* interrupt and drives the reference signals for temperature measurement. 
*
*****************************************************************************/
void InitializeSystem (void)
{
    CyGlobalIntEnable;
    
    /* Enable BLE and related resouces */
    EnableBLE();
    
    /* Start UART */
    UART_DEB_Start();
    CyDelay(100);// waiting for clear start after power on
    UART_DEB_UartPutCRLF(' ');
    UART_DEB_UartPutString("Temperature sensor DS18S20:\r\n");
    
    /* Start OneWire */
    OneWire_Start();
    isr_Timer_StartEx(isr_Timer);
}

/* [] END OF FILE */
