/* ============================================================================
 * DS18x8: MAXIM DS18B20 Digital Thermometer component (v 0.0)
 * Read temperature simultaaneously from up to 8 DS18B20 sensors
 *
 * based on original OneWire code by Evg. Pavlov <pavloven>
 * http://mylab.wmsite.ru/moi-razrab/cypress-psoc/temperature-logger/
 * http://mylab.wmsite.ru/moi-razrab/cypress-psoc/psoc-user-module-library/
 * ============================================================================
 * PROVIDED AS-IS, NO WARRANTY OF ANY KIND, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * FREE TO SHARE, USE AND MODIFY UNDER TERMS: CREATIVE COMMONS - SHARE ALIKE
 * ============================================================================
*/


#if !defined(`$INSTANCE_NAME`_H) 
#define `$INSTANCE_NAME`_H


#include "cytypes.h"        //macros

    
/***************************************
*        defines 
***************************************/
//#define  `$INSTANCE_NAME`_NumSensorsMax  (uint8) 8u    

#define Tinact   20u        //us, Inactive before next signal
#define TMtr0    50u        //Data bit 0 read,write 15-60us
#define TMtr1    10u        //Data bit 1 read,write 1-15us
#define RST_MAX 480u        //min 480 us
#define T_conv  750u        //sensor conversion time ~750ms (12bit)
 
#define HIGH 1u             // drive 1
#define LOW  0u             // drive 0
#define SET_ALL_OUT   255u  // select all [11111111] (select mask = 2^8-1)
#define SET_ALL_INP   0u    // set to read - disable all
       
#define T_OFF (int16) -4096 // missing sensor temperature, -4096 <->-256 C
#define Str_OFF       "-"   // missing sensor report string
 
    
    
/***************************************
*        Types 
***************************************/
    
typedef struct `$INSTANCE_NAME`_TSensor {
    uint16 Temperature;     //encoded temperature reading
    uint8  present;         //sensor present 
} `$INSTANCE_NAME`_SensorBuffer;
struct `$INSTANCE_NAME`_TSensor `$INSTANCE_NAME`_Sensor[8]; //array of sensors




volatile CYBIT `$INSTANCE_NAME`_DataReady; //semaphore flag


/***************************************
*        Component parameters 
***************************************/

#define `$INSTANCE_NAME`_NumSensors `$Num_Sensors`

    


    
/***************************************
*        Function Prototypes 
***************************************/

void  `$INSTANCE_NAME`_Start();                     // init component
void  `$INSTANCE_NAME`_Stop();                      // stop component
uint8 `$INSTANCE_NAME`_CheckPresence();             // check sensor presence, returns 8-bit bus state
uint8 `$INSTANCE_NAME`_SendTemperatureRequest();    // start temperature conversion //todo Ret: Bus presence?
uint8 `$INSTANCE_NAME`_ReadTemperature();           // read sensor conversion result 
uint8 `$INSTANCE_NAME`_BusState();                  // 8-bit bus state: 1-sensor present, 0-sensor read failure


float `$INSTANCE_NAME`_GetTemperatureAsFloat  (uint8 index);  // convert to degC, returned as float
int16 `$INSTANCE_NAME`_GetTemperatureAsInt100 (uint8 index);  // convert to degC x100, truncated to int16 
char* `$INSTANCE_NAME`_GetTemperatureAsString (uint8 index);  // convert to degC, returned as string

char* itoa10(int value, char* result);              // helper function, int->string

#endif // !defined(`$INSTANCE_NAME`_H) 

/* [] END OF FILE */
