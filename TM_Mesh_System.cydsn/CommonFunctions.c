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
void InitializeSystem(void)
{
	/* Enable global interrupts. */
	CyGlobalIntEnable;
	
	/* Start BLE component and Register the generic Event callback function */
	CyBle_Start(GenericEventHandler);
	
	/* Configure the Watchdog (WDT) timer for 100 millisecond timing */
	InitializeWatchdog(WATCHDOG_COUNT_VAL);
    
    /* Start OneWire */
    OneWire_Start();
    isr_Timer_StartEx(isr_Timer);

	#ifdef ENABLE_ADV_DATA_COUNTER
	new_advData = *cyBle_discoveryModeInfo.advData;
	
	if( cyBle_discoveryModeInfo.advData->advDataLen < 29)
	{
		/* Initialize the DataCounter data in advertisement packet. This is custom data in 
		* ADV packet and used to track whether the RGB LED data is latest or not */
		new_advData.advData[cyBle_discoveryModeInfo.advData->advDataLen] = CUSTOM_ADV_DATA_MARKER;	
		new_advData.advData[cyBle_discoveryModeInfo.advData->advDataLen+1] = dataADVCounter;
		new_advData.advDataLen = cyBle_discoveryModeInfo.advData->advDataLen+2;
	}
	
	/* Assign the new ADV data to stack */
	cyBle_discoveryModeInfo.advData = &new_advData;
	#endif
    
    /* Start UART */
	UART_Start();
	#ifdef DEBUG_ENABLED
		UART_Start();
		UART_UartPutString("--------------------------Mesh Flood------------------------------------------");
		UART_UartPutCRLF(' ');
	#endif
}


// Reverses a string 'str' of length 'len' 
void reverse(char* str, int len) 
{ 
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 
  
// Converts a given integer x to string str[].  
// d is the number of digits required in the output.  
// If d is more than the number of digits in x,  
// then 0s are added at the beginning. 
int intToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
  
    // If number of digits required is more, then 
    // add 0s at the beginning 
    while (i < d) 
        str[i++] = '0'; 
  
    reverse(str, i); 
    str[i] = '\0'; 
    return i; 
} 
  
// Converts a floating-point/double number to a string. 
void ftoa(float n, char* res, int afterpoint) 
{ 
    // Extract integer part 
    int ipart = (int)n; 
  
    // Extract floating part 
    float fpart = n - (float)ipart; 
  
    // convert integer part to string 
    int i = intToStr(ipart, res, 0); 
  
    // check for display option after point 
    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
  
        // Get the value of fraction part upto given no. 
        // of points after dot. The third parameter  
        // is needed to handle cases like 233.007 
        fpart = fpart * 100; 
  
        intToStr((int)fpart, res + i + 1, afterpoint); 
    }
}

/* [] END OF FILE */
