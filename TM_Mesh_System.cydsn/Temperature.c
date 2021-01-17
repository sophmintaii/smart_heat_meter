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
#include <stdio.h>
#include "Temperature.h"
#include "CommonFunctions.h"
#include "main.h"


/* Enable Interrupts */
CY_ISR(isr_Timer) 
{
    flag_Timer = 1;
}


/*****************************************************************************
* Function Name: GetTemperature()
******************************************************************************
* Description:
* Tries to establish connection with sensor and if established -
* Returns temperature measured by DS18S20 sensor when data is ready
*
* Parameters:
* (CYBIT) flag_Timer - timer used by DS18S20 (look for in TopDesign.cysch)
*
* Return:
* (float) temperature - temperature
*
*****************************************************************************/
float GetTemperature(CYBIT flag_Timer) {
    float temperature;
    
    // Try to establish connection to buss and return value if established
    for (int i = 0; i < 50; i++) {
        temperature = ProcessTemperature(flag_Timer);
        if (temperature != 0) {
            return temperature;
        }
    }
    return 0;
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
     
        CyDelay(400);
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
    float temperature = OneWire_GetTemperatureAsFloat(0);
    // SendTemperarureToUart(float temperature);
 
    return temperature;
}


void SendTemperarureToUart(float temperature) {
    char strMsg[80];
    char buf[6];
    
    // convert float to string
    if (temperature) {
        ftoa(temperature, buf, 2);
    } else {
        buf[0] = '0';
    }
    
    sniprintf(strMsg, 80, "Temperature: %s", buf);
    
    UART_UartPutCRLF(' ');
    UART_UartPutString(strMsg);   
    UART_UartPutCRLF(' ');
}


void SendTempArrayToUart(float* array) {
    UART_UartPutCRLF(' ');
    UART_UartPutString("----- Temperature Array -----");
    UART_UartPutCRLF(' ');
    
    for (int i = 0; i < DEVICE_NUMBER; i++) {
        char strMsg[80];
        char buf[6];
        buf[0] = '\0';
        
        if (array[i]) {
            ftoa(array[i], buf, 2);
        } else {
            buf[0] = '0';
        }
    
        sniprintf(strMsg, 80, "%d.: %s", i, buf);
        UART_UartPutString(strMsg);   
        UART_UartPutCRLF(' ');
    }
    UART_UartPutCRLF(' ');
}

/* [] END OF FILE */
