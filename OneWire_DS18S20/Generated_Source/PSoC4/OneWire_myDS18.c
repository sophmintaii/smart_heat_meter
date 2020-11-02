/* ============================================================================
 * myDS18x4: MAXIM DS18B20 Digital Thermometer component (v 0.0)
 * Read temperature simultaaneously from up to 8 DS18B20 sensors 
 *
 * based on original OneWire code by <pavloven>
 * http://mylab.wmsite.ru/moi-razrab/cypress-psoc/temperature-logger/
 * http://mylab.wmsite.ru/moi-razrab/cypress-psoc/psoc-user-module-library/
 * ============================================================================
 * PROVIDED AS-IS, NO WARRANTY OF ANY KIND, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * FREE TO SHARE, USE AND MODIFY UNDER TERMS: CREATIVE COMMONS - SHARE ALIKE
 * ============================================================================
*/


#include <OneWire.h>
#include <project.h>


//static char strMsg1[64];//output UART buffer, debug only..

#define GetBit(Value, BitNo) ((Value >> BitNo) & (uint8)0x01)   //macro to read a bit,  returns 0 or 1



//uint8 OneWire_BusPresence; // 8-bit bus state: 1-sensor present, 0-sensor read failure
uint8 BusPresence; // 8-bit bus state: 1-sensor present, 0-sensor read failure

//static volatile CYBIT DataReady = 0; //semaphore   

//==============================================================================
//                  ISR Timer data ready to read
//==============================================================================
//CY_ISR_PROTO(OneWire_IRQDataReady); //ISR proto
CY_ISR(OneWire_IRQDataReady) // ISR Timer data ready to read
{
    //DataReady = 1;
    OneWire_DataReady = 1;
}


//==============================================================================
//                              Read Bit
//==============================================================================

uint8 R_BitBus(void) //  Read a single bit off the 1-WIRE bus
{  
    CyDelayUs(Tinact);  // Inactive before next signal. =20us
    //variants: http://www.cypress.com/?rID=38854&cache=0
    
    OneWire_ControlReg_SEL_Write(SET_ALL_OUT);
    OneWire_ControlReg_DRV_Write(LOW);  //Drive LOW selected pin

    CyDelayUs(TMtr1);   // read 1us, write 1-15us
    OneWire_ControlReg_DRV_Write(HIGH);  //Drive HIGH selected pin
    
	CyDelayUs(5);       // check in 5 usec
    
    //prepare read
    OneWire_ControlReg_SEL_Write(SET_ALL_INP);   // all outputs disable
    OneWire_ControlReg_DRV_Write(LOW); // Drive LOW 
    
    uint8 result = OneWire_StatusReg_BUS_Read();
    return (result);
}

//==============================================================================
//                              Write Bit
//==============================================================================

void W_Bit(uint8 payload) // Write a single bit to the 1-WIRE bus. 
{
	CyDelayUs(Tinact);  //Inactive before next signal.
    OneWire_ControlReg_DRV_Write(LOW); // Drive LOW enabled outputs

    if(payload==0)	CyDelayUs(TMtr0); //If its a 0 to write, TMtr0 = 50us
	else     		CyDelayUs(TMtr1); //If its a 1 to write, TMtr1 = 10us
        
    OneWire_ControlReg_DRV_Write(HIGH); // Drive HIGH enabled outputs
}
 
//==============================================================================
//                              Write a byte
//==============================================================================

void Write8(uint8 payload) //Write a byte to the slave.
{
	uint8 BitPayload,  shiftcount;
    
    OneWire_ControlReg_SEL_Write(SET_ALL_OUT); // enable all outputs [11]
    
	for (shiftcount=0; shiftcount<=7;shiftcount++) 
    {
        BitPayload = (payload >> shiftcount) & 0x01; //starting with LSB
        W_Bit(BitPayload);
    }
}  


//==============================================================================
//                              Bus Reset
//==============================================================================
   
uint8 BusReset() //Pulldown the required "Bus Reset". 
{
    static struct OneWire_TSensor Sensor_off = {T_OFF, 0};
    uint8 i;
    
    // reset all sensor Temerature and presence
    for (i=0; i<8; i++) {OneWire_Sensor[i] = Sensor_off;}
    
    
    uint8 BusPin=0;    //bus state

    OneWire_ControlReg_DRV_Write(LOW);         // Drive LOW enabled outputs
    OneWire_ControlReg_SEL_Write(SET_ALL_OUT); // enable all outputs [1111]
    
 
	CyDelayUs(RST_MAX); // send RESET pulse, 480usec min
    OneWire_ControlReg_DRV_Write(HIGH); // Drive HIGH enabled outputs
    
    CyDelayUs(5);       // check bus shorted
    
    //prepare to read
    OneWire_ControlReg_SEL_Write(SET_ALL_INP); // set all as inputs [0000]
    OneWire_ControlReg_DRV_Write(LOW);         // Drive LOW enabled outputs
    
    //todo: not tested, check status for all sensors
    //if (OneWire_StatusReg_BUS_Read()==0x00) return(0xFF); //bus shorted, exit , won't exit?
    
    //returns bit1 if unplugged, 0 if shorted to GND thru 5k
    //reading StatusReg_BUS affects BusPin result
    //tmp = OneWire_StatusReg_BUS_Read();
    //sprintf(strMsg1,"tmp=%d\r\n", tmp);
    //while(USBUART_1_CDCIsReady() == 0u);    // Wait till component is ready to send more data to the PC 
    //USBUART_1_PutString(strMsg1);
        
    CyDelayUs(55);      // check PRESENCE in 15-60usec  (60-240 ?????)
    
    
    BusPin = OneWire_StatusReg_BUS_Read();   // Read state: bit=0 if present 1 if unplugged
    
    //sprintf(strMsg1,"Bus=%d\r\n", BusPin);
    //while(USBUART_1_CDCIsReady() == 0u);    // Wait till component is ready to send more data to the PC 
    //USBUART_1_PutString(strMsg1);  
    
    CyDelayUs(200);     // wait for DS18 to transmit PRESENCE  (60-240 usec) (why wait?)
    
    //return((~BusPin) & 15u);     // Return bus state: 1-present, 0-absent  (originally 0-present, 1-fault)
    return((~BusPin) & 255u);     // Return bus state: 1-present, 0-absent  (originally 0-present, 1-fault)
}

/*
//////////////////////////////////////////////////////////////////////////////
// OW_RESET - performs a reset on the one-wire bus and
// returns the presence detect. Reset is 480us, so delay
// value is (480-24)/16 = 28.5 - we use 29. Presence checked
// another 70us later, so delay is (70-24)/16 = 2.875 - we use 3.
//
unsigned char ow_reset(void)
{
    unsigned char presence;
    DQ = 0; //pull DQ line low
    delay(29); // leave it low for 480us
    DQ = 1; // allow line to return high
    delay(3); // wait for presence
    presence = DQ; // get presence signal
    delay(25); // wait for end of timeslot
    return(presence); // presence signal returned
} // 0=presence, 1 = no part
*/


//==============================================================================
//                         start temperature conversion
//==============================================================================

uint8 OneWire_SendTemperatureRequest() // start temperature conversion 
{   
    //OneWire_BusPresence = BusReset(); // Reset ( > 480 usec )
    BusPresence = BusReset(); // Reset ( > 480 usec ) 
    
    //todo: there will be no reporting...
    //if (OneWire_BusPresence == 0) return (0); // no sensors found //todo: no reporting?
    //if (OneWire_BusPresence == 0) {
    if (BusPresence == 0) {
        OneWire_DataReady = 1; //proceed directly to reporting
        return (0);                     // no sensors found
    }
    
    //OneWire_ControlReg_SEL_Write(ALL); // enable all outputs [1111]
    Write8(0xCC);       // send command Skip_ROM  (0xCCÍ)  
    Write8(0x44);       // send command for temperature conversion  (0x44Í)

    OneWire_Trigger_Write(1);   // trigger Async delayed reading
    
    //return (OneWire_BusPresence);
    return (BusPresence);
}


//==============================================================================
//                          Read sensor Temperature
//==============================================================================

uint8 OneWire_ReadTemperature() // data is ready - read sensor's Temperature LSB & MSB 
{
    uint8 Bus;  // read state of bus  
    uint8 mask; // sensor presence mask
    uint8 i, shiftcount;
    //struct TSensor s[8]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}; //array of sensors {Temperature, presence}, must reset to "0"
    struct OneWire_TSensor s[8]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}; //array of sensors {Temperature, presence}, must reset to "0"
    
    if (!OneWire_DataReady) return  (0);   // sensor not ready for temperature reading
    OneWire_DataReady = 0;                 // reset flag
    //if (!DataReady) return  (0);             // sensor not ready for temperature reading
    //DataReady = 0;                           // reset flag
    
    //if (OneWire_BusPresence == 0) return (0); // no sensors found on temperature request, exit 
    if (BusPresence == 0) return (0); // no sensors found on temperature request, exit 
    
    
    //OneWire_BusPresence = BusReset();  // Reset  ( > 480 usec )
    BusPresence = BusReset();  // Reset  ( > 480 usec )
    //if (OneWire_BusPresence == 0) return (0); // no sensors found 
    if (BusPresence == 0) return (0); // no sensors found 
    
    
    //mask = OneWire_BusPresence;
    mask = BusPresence;
        
    for (i=0; i<OneWire_NumSensors; i++) {s[i].present = GetBit(mask, i);} //
    
    
    //OneWire_ControlReg_SEL_Write(SET_ALL_OUT); // enable all for outputs [1111] - can use as selection mask
    Write8(0xCC);   // send command Skip_ROM  (0xCC)    
    Write8(0xBE);   // send command to read buffer memory (0xBE)
    
    // read first two bytes of the memory DS18B20
    for (shiftcount=0; shiftcount<=11; shiftcount++) // read bytes 0 to 11
    {
        Bus = R_BitBus(); //read all sensors in parallel
        
        for (i=0; i<OneWire_NumSensors; i++) //
        {
            if (s[i].present) //ignore channels without sensor
                s[i].Temperature |= GetBit(Bus, i) << shiftcount; // staff Temperature begining with LSB //todo: SetBit
        }
    }
    
    for (i=0; i<8; i++) //8-is maximum number of sensors in current implementation
    {
        if (s[i].present)   
            {if (s[i].Temperature >= 2048) s[i].Temperature -= 4096;} // roll over for negative temperatures
        else
            {s[i].Temperature = T_OFF;} // set some "defunct" value if sensor absent 
        
        OneWire_Sensor[i] = s[i]; //record Temperature and presence
    }
    
    return(mask); //return BusPresence
}


//==============================================================================
// Convert DS18B20 encoded temperature to float value (degC)
//==============================================================================

float OneWire_GetTemperatureAsFloat (uint8 index) // 
{    
    int16 Val = OneWire_Sensor[index].Temperature;
    return ( (float) Val * 0.0625f);
}


//==============================================================================
// Convert DS18B20 temperature (degC) as *100 value rounded to integer
// e.g. -38.0625 -> "-3806" 
//==============================================================================

int16 OneWire_GetTemperatureAsInt100 (uint8 index) 
{
    //int16 Val = OneWire_Sensor[index].Temperature;
    //return ((Val * 100u) >> 4); //todo: this truncating has rounding errors 19->18, 44->43, 69->68, 94->93, 
    return (0); //todo: this truncating has rounding errors 19->18, 44->43, 69->68, 94->93,
}


//==============================================================================
// C++ version 0.4 char* style "itoa":
// Written by Lukás Chmela
// Released under GPLv3.
// http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
// here: modified for radix 10 only 
//==============================================================================

char* itoa10(int value, char* result)
{
    const uint8 base = 10u;
	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;
	
	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "9876543210123456789" [9 + tmp_value - value * base];
	} while ( value );
	
	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}



//==============================================================================
// Convert DS18B20 temperature (degC) as string
// e.g. -38.0625 <-> "-38.0625"
//==============================================================================

char* OneWire_GetTemperatureAsString (uint8 index) 
{
    char TempStr[13]={};    // buffer string for current temperature //warning
    char* result = TempStr;
    char buf[8];            // buffer
    
    CYBIT sign;             // Temp sign
    int grad;               // integer portion w/o sign
    uint8 frac;             // fractional portion
    
    //static const char *str[] = {".0", ".1", ".1", ".2", ".3", ".3", ".4", ".4", ".50", ".6", ".6", ".7", ".8", ".8", ".9", ".9"}; //%.1
    static const char *str[] = {".00", ".06", ".13", ".19", ".25", ".31", ".38", ".44", ".50", ".56", ".63", ".69", ".75", ".81", ".88", ".94"};// %.2
    //static const charr *str[] = {".000", ".063", ".125", ".188", ".250", ".313", ".375", ".438", ".500", ".563", ".625", ".688", ".750", ".813", ".875", ".938"}; // %.3
    //static const char *str[] = {".0000", ".0625", ".1250", ".1875", ".2500", ".3125", ".3750", ".4375", ".5000", ".5625", ".6250", ".6875", ".7500", ".8125", ".8750", ".9375"}; // %.4
     
    // exit and return pre-defined string if no sensor present
    if (!OneWire_Sensor[index].present) return (Str_OFF);

        
    int16 Val = OneWire_Sensor[index].Temperature;
    sign = (Val < 0);                       // remember sign prior to shift     
    if (sign) grad = -Val; else grad = Val; //grad = abs(Temp); no need for stdlib.h
    frac = grad & 15;                       //index for fractional part
    grad = grad >> 4;                       //get integer portion
    
    if (sign) strcat(TempStr, itoa10(-grad, buf)); 
    else      strcat(TempStr, itoa10( grad, buf));
    
    strcat(TempStr, str[frac]); //add fractional part
    
    return (result);
}

//==============================================================================
// Initialize and Start component
//==============================================================================
void OneWire_Start() // Initialize component 
{
    
    OneWire_isr_DataReady_StartEx(OneWire_IRQDataReady);
    
    //configure and start 1-shot timer for 750ms data conversion delay
    OneWire_TimerDelay_WriteCounter(T_conv);   // set time for conversion 750ms
    OneWire_TimerDelay_Start();                // Initialize TimerDelay
    //DataReady = 0;                               // ready for temperature request
    OneWire_DataReady = 0;                     // semaphor flag
}

//==============================================================================
// Disable component
//==============================================================================
void OneWire_Stop() 
{
    OneWire_TimerDelay_Stop(); // disable timer
}

//==============================================================================
// Return 8-bit bus state: 1-sensor present, 0-sensor read failure
//==============================================================================
uint8 OneWire_BusState()
{
    //return( OneWire_BusPresence );   
    return( BusPresence );   
}

//==============================================================================
// Function to check sensors presence
// Return 8-bit bus state: 1-sensor present, 0-sensor read failure
//==============================================================================
uint8 OneWire_CheckPresence()
{  
    BusPresence = BusReset(); // Reset ( > 480 usec ) 
    return( BusPresence );   
}


//==============================================================================
//    Read-only flag (takes 31 tick)              
//==============================================================================
//volatile CYBIT OneWire_DataReady()
//{
//    return (DataReady);
//}

/* [] END OF FILE */

//static inline int get_a(void)
//{
//    extern int a_var;
//    return a_var;
//}
//extern int my_project_a;
  
