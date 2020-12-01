/****************************************************************************
* File Name: main.c
*
* Description:
* This file merges the whole code and send temperature
* measurements via BLE and UART.
*
* Authors: Yaroslav Morozevych, Sophiia Myntiuk, Yana Mularska
*
*****************************************************************************/


/*****************************************************************************
* Included common headers
*****************************************************************************/
#include <project.h>
#include <stdlib.h>
#include <stdio.h>


/*****************************************************************************
* Included header files with the initialization of all need functions
*****************************************************************************/
#include "CommonFunctions.h"
#include "WatchdogTimer.h"
#include "BLE_HTSS.h"
#include "Temperature.h"


/*****************************************************************************
* Function Name: main()
******************************************************************************
* Description:
* Measure temperature every second and  
* Send result to Terminal using UART and via BLE
*
*****************************************************************************/
int main()
{
    /* Local variable used to store temperature information */
    float temperature;
    
    /* Initialize the complete system */
    InitializeSystem();
    /* Force first measument instantly */
    flag_Timer = 1;
    
    for(;;) 
    { 
        /* Process all pending BLE events in the stack */
        CyBle_ProcessEvents();
        
        /***********************************************************************
        * Wait for connection established with Central device
        ***********************************************************************/
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            /* Process all pending BLE events in the stack */
            CyBle_ProcessEvents();
            /* Periodically measure temperature and send results to the Client */
            if(SystemFlag & WAKEUP_SOURCE_WDT)
            {
                /* Clear WDT wakeup source flag */
                SystemFlag &= ~WAKEUP_SOURCE_WDT;
                /* Measure temperature */
                temperature = ProcessTemperature(flag_Timer);
                /* Send temperature information over BLE */
                ProcessBLE(temperature);
            }
        }
    }
    return 0;
}