/*****************************************************************************
* File Name: CommonFunctions.h
*
* Description:
* This file provides the declarations of the common system functions.
*
*****************************************************************************/
#if !defined (_COMMON_FUNCTIONS_H)
#define _COMMON_FUNCTIONS_H

#include <project.h>
#include <math.h> 
#include <stdio.h> 
    
#include "main.h"
#include "debug.h"
#include "ble_process.h"
#include "WDT.h"
#include "CommonFunctions.h"
#include "Temperature.h"
    
/*****************************************************
*             Pre-processor Directives
*****************************************************/ 
//#define ENABLE_ADV_DATA_COUNTER
//#define DEBUG_ENABLED

/*****************************************************************************
* CONSTANT Declarations
*****************************************************************************/
extern uint8 dataADVCounter;
    
#ifdef ENABLE_ADV_DATA_COUNTER
extern CYBLE_GAPP_DISC_DATA_T  new_advData;
extern uint8 potential_node_found;
extern uint8 potential_node_bdAddr[6];
extern uint8 potential_node_bdAddrType;
#endif

/*****************************************************************************
* Function Declarations
*****************************************************************************/
extern void InitializeSystem(void);
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);

#endif 

/* [] END OF FILE */
