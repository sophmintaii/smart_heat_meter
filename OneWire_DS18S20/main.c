/* ===========================================================================================
 * Digital Thermometer demo project
 *
 * uses
 * DS18x4: MAXIM DS18B20 Digital Thermometer component (v 0.0)
 * Read temperature simultaneously from up to 8 DS18B20 sensors
 * 
*/

#include <project.h>
#include <stdio.h>


static volatile CYBIT flag_Timer = 0 ; //semaphore   
CY_ISR(isr_Timer) // ISR Timer to report temperature at regular interval
{
    flag_Timer = 1;
}

void ReportTemperature (void); // convert temperature code to deg C and send to UART


void Initialize(void)
{
    CyGlobalIntEnable;  // Uncomment this line to enable global interrupts.
        
    CyDelay(100);// waiting for clear start after power on
    
    OneWire_Start();
    
    isr_Timer_StartEx(isr_Timer);
}

int main()
{

    Initialize();
    
    flag_Timer = 1; // force first measument instantly
    
    for(;;) 
    { 
        
        if(flag_Timer) //read DS18S20 on timer, intervals >1sec
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
    return 0;
}


void ReportTemperature(void) 
{
    printf( "%s\n" , OneWire_GetTemperatureAsString(0) );      
}
