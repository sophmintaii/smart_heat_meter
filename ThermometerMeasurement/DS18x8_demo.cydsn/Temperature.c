/****************************************************************************
* File Name: Temperature.c
*
* Description:
* This file implements the common functions for temperature measuring.
*
* Authors: Yaroslav Morozevych, Sophiia Myntiuk, Yana Mularska
*
*****************************************************************************/


/*****************************************************************************
* Included headers
*****************************************************************************/
#include <project.h>
#include "Temperature.h"


/* Enable Interrupts */
CY_ISR(isr_Timer) 
{
    flag_Timer = 1;
}


/*****************************************************************************
* Function Name: ProcessTemperature()
******************************************************************************
* Description:
* Returns temperature measured by DS18S20 sensor when data is ready
*
* Parameters:
* (CYBIT) flag_Timer - timer used by DS18S20 (look for in TopDesign.cysch)
*
* Return:
* (float) temperature - temperature
*
*****************************************************************************/
float ProcessTemperature(CYBIT flag_Timer) {
    float temperature = 0;
 
    if(flag_Timer) //read DS18B20 on timer, intervals > 1sec
	{   
        flag_Timer = 0;
        OneWire_SendTemperatureRequest();                                       
    }
    
    if (OneWire_DataReady) // DS18 completed temperature measurement - begin read dataa
	{   
        OneWire_ReadTemperature();
        temperature = ReportTemperature();
    }
    return temperature;
}



/*****************************************************************************
* Function Name: ReportTemperature()
******************************************************************************
* Description:
* Convert temperature code to degC and 
* Send result to Terminal using UART
*
* Parameters:
* None
*
* Return:
* (float) temperature - temperature
*
*****************************************************************************/
float ReportTemperature(void) 
{
    char strMsg[80]={};         // output UART buffer
    char buf[8];                // temp buffer
    static uint32 counter = 0;  // sample counter
    
    counter++; 
    float temperature = OneWire_GetTemperatureAsFloat(0);
    
    strcat(strMsg, itoa10(counter, buf)); strcat(strMsg, "\t");
    strcat(strMsg, OneWire_GetTemperatureAsString(0)); strcat(strMsg, "\t");

    UART_DEB_UartPutString(strMsg);  
    UART_DEB_UartPutCRLF(' ');
    return temperature;
}

/* [] END OF FILE */
