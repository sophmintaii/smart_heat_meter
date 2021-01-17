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
* Included header files with the initialization of all need functions
*****************************************************************************/
#include <project.h>
#include "main.h"
#include "ble_process.h"
#include "CommonFunctions.h"

#define DEVICE_NUMBER 4


/*****************************************************
*                  Variables
*****************************************************/ 
volatile uint16 current_watchdog_counter;
CYBLE_GATTS_WRITE_REQ_PARAM_T TemperatureStorage;



  

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*       Entry point for the firmware, Starts the system and continuously processes
* Application and BLE events.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main()
{
    /* Initialize system */	
	InitializeSystem();
    flag_Timer = 1;
    GREEN_LED_Pin_Write(1);
	
    float temps[4];
    TemperatureStorage.handleValPair.value.val = temps;
    
	#ifdef DEBUG_ENABLED
		UART_UartPutString("Sytem Started ");
		UART_UartPutCRLF(' ');
	#endif
	
    
    for(;;)
    {
        //float tmp = ProcessTemperature(flag_Timer);
		/* Process BLE Events. This function generates the respective 
		* events to application layer */
		CyBle_ProcessEvents();

		/* If flag is set, then switch the GAP role between Peripheral and 
		* Central. This function disconnects existing connection, if any, 
		* before switching role. Depending on switched role, the system will
		* either start scanning or start advertisement */
		SwitchRole();
		
		/* If a valid node is found, then this function will initiate a connection 
		* to that node. */
		ConnectToPeripheralDevice();
		
		/* This function will restart scanning when earlier connection has been
		* disconnected. This function also checks internal counter and sets flag to
		* switch role from Central to Peripheral when the count is above set value. */
		RestartCentralScanning();
    }
}
