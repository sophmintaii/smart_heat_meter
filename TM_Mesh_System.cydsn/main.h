/*******************************************************************************
* File Name: main.h
*
* Version: 1.0
*
* Description:
*  This is header file containing function declarations for all application related
* functions as well as Macros.
*
*******************************************************************************/
#if !defined(MAIN_H)
#define MAIN_H
    
#include <project.h>
#include <stdlib.h>
#include <stdio.h>
    
#include "debug.h"
#include "ble_process.h"
#include "WDT.h"
#include "CommonFunctions.h"
#include "Temperature.h"

/*****************************************************
*             Pre-processor Directives
*****************************************************/ 
#define TEMPERATURE_OUTPUT_ENABLED
//#define DEBUG_ENABLED
//#define ENABLE_ADV_DATA_COUNTER
//#define ENABLE_CENTRAL_DISCOVERY

/*****************************************************
*                  Variables
*****************************************************/ 
#define DEVICE_NUMBER 4    

volatile uint16 current_watchdog_counter;
CYBLE_GATTS_WRITE_REQ_PARAM_T TemperatureStorage;
const int deviceIndex = 1;

/*****************************************************
*                  Enums and macros
*****************************************************/ 
#define TRUE								1
#define FALSE								0
#define BLE_PERIPHERAL						1
#define BLE_CENTRAL							2
	
#define CENTRAL_STATE_SPAN					45
#define PERIP_RGB_HOLD_TIME					10

#define WatchDog_CurrentCount()				(current_watchdog_counter)
    
void ftoa(float n, char* res, int afterpoint);

#endif


/* [] END OF FILE */
