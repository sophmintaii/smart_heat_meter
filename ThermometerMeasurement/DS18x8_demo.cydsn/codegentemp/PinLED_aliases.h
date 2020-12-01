/*******************************************************************************
* File Name: PinLED.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PinLED_ALIASES_H) /* Pins PinLED_ALIASES_H */
#define CY_PINS_PinLED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PinLED_0			(PinLED__0__PC)
#define PinLED_0_PS		(PinLED__0__PS)
#define PinLED_0_PC		(PinLED__0__PC)
#define PinLED_0_DR		(PinLED__0__DR)
#define PinLED_0_SHIFT	(PinLED__0__SHIFT)
#define PinLED_0_INTR	((uint16)((uint16)0x0003u << (PinLED__0__SHIFT*2u)))

#define PinLED_INTR_ALL	 ((uint16)(PinLED_0_INTR))
#define PinLED_LED			(PinLED__LED__PC)
#define PinLED_LED_PS		(PinLED__LED__PS)
#define PinLED_LED_PC		(PinLED__LED__PC)
#define PinLED_LED_DR		(PinLED__LED__DR)
#define PinLED_LED_SHIFT	(PinLED__LED__SHIFT)
#define PinLED_LED_INTR	((uint16)((uint16)0x0003u << (PinLED__0__SHIFT*2u)))


#endif /* End Pins PinLED_ALIASES_H */


/* [] END OF FILE */
