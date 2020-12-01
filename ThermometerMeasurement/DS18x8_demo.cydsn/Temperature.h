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

    
/*****************************************************************************
* Static variables
*****************************************************************************/
static volatile CYBIT flag_Timer = 0 ;
// ISR Timer to report temperature at regular interval
CY_ISR(isr_Timer);
    
    
/*****************************************************************************
* Function Declarations
*****************************************************************************/
float ProcessTemperature(CYBIT flag_timer);
float ReportTemperature (void);


#endif
/* [] END OF FILE */
