/*****************************************************************************
* File Name: Temperature.h
*
* Description:
* This file provides the declarations of functions of temparature measuring.
*
*****************************************************************************/
#if !defined (_TEMPERATURE_H)
#define _TEMPERATURE_H
    
#include <project.h>
#include <stdio.h>
    
#define DEVICE_NUMBER 4

    
/*****************************************************************************
* Static variables
*****************************************************************************/
static volatile CYBIT flag_Timer = 1;
// ISR Timer to report temperature at regular interval
CY_ISR(isr_Timer);
    
    
/*****************************************************************************
* Function Declarations
*****************************************************************************/
float GetTemperature(CYBIT flag_Timer);
float ProcessTemperature(CYBIT flag_timer);
float ReportTemperature (void);
void SendTemperarureToUart(float temperature);
void SendTempArrayToUart(float* array);

#endif
/* [] END OF FILE */
