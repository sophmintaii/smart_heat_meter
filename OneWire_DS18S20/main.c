/* ===========================================================================================
 * Digital Thermometer demo project
 *
 * uses
 * DS18x4: MAXIM DS18B20 Digital Thermometer component (v 0.0)
 * Read temperature simultaneously from up to 8 DS18B20 sensors
 * 
 *   
 *
 * ===========================================================================================
 * PROVIDED AS-IS, NO WARRANTY OF ANY KIND, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * FREE TO SHARE, USE AND MODIFY UNDER TERMS: CREATIVE COMMONS - SHARE ALIKE
 * ===========================================================================================
*/

#include <project.h>
//#include <stdio.h> //sprintf

/*
#if defined (__GNUC__)
    // Add an explicit reference to the floating point printf library
    // to allow the usage of floating point conversion specifiers.
    // This is not linked in by default with the newlib-nano library.
    asm (".global _printf_float");
#endif
*/

static volatile CYBIT flag_Timer = 0 ; //semaphore   
CY_ISR(isr_Timer) // ISR Timer to report temperature at regular interval
{
    flag_Timer = 1;
}

//===========================================
// Function prototypes
//===========================================

void ReportTemperature (void); // convert temperature code to deg C and send to UART


void Initialize(void)
{
    CyGlobalIntEnable;  // Uncomment this line to enable global interrupts.
        
    UART_DEB_Start();
    CyDelay(100);// waiting for clear start after power on
    UART_DEB_UartPutCRLF(' ');
    UART_DEB_UartPutString("Temperature sensor Maxim DS18B20:\r\n");
    
    OneWire_Start();
    
    isr_Timer_StartEx(isr_Timer);
}


void main()
{

    Initialize();
    
    flag_Timer = 1; // force first measument instantly
    
    for(;;) 
    { 
        
        if(flag_Timer) //read DS18B20 on timer, intervals >1sec
    	{   
            flag_Timer = 0;
            OneWire_SendTemperatureRequest(); //                                        
        }
        
        if (OneWire_DataReady) // DS18 completed temperature measurement - begin read dataa
    	{   
            OneWire_ReadTemperature(); // 
            ReportTemperature();
        }    
        
    }   

} //main




//==============================================================================
// Convert temperature code to degC and 
// Send result to Terminal using UART
//==============================================================================

void ReportTemperature(void) 
{
    char strMsg[80]={};         // output UART buffer
    char buf[8];                // temp buffer
    static uint32 counter = 0;  // sample counter
    
    counter++; 
   

             
    strcat(strMsg, itoa10(counter, buf)); strcat(strMsg, "\t");
    strcat(strMsg, OneWire_GetTemperatureAsString(0)); strcat(strMsg, "\t");

       
    UART_DEB_UartPutString(strMsg);  
    UART_DEB_UartPutCRLF(' ');
}

