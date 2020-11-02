/*******************************************************************************
* File Name: PinLED.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PinLED_H) /* Pins PinLED_H */
#define CY_PINS_PinLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinLED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PinLED_Write(uint8 value) ;
void    PinLED_SetDriveMode(uint8 mode) ;
uint8   PinLED_ReadDataReg(void) ;
uint8   PinLED_Read(void) ;
uint8   PinLED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PinLED_DRIVE_MODE_BITS        (3)
#define PinLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinLED_DRIVE_MODE_BITS))

#define PinLED_DM_ALG_HIZ         (0x00u)
#define PinLED_DM_DIG_HIZ         (0x01u)
#define PinLED_DM_RES_UP          (0x02u)
#define PinLED_DM_RES_DWN         (0x03u)
#define PinLED_DM_OD_LO           (0x04u)
#define PinLED_DM_OD_HI           (0x05u)
#define PinLED_DM_STRONG          (0x06u)
#define PinLED_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PinLED_MASK               PinLED__MASK
#define PinLED_SHIFT              PinLED__SHIFT
#define PinLED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinLED_PS                     (* (reg32 *) PinLED__PS)
/* Port Configuration */
#define PinLED_PC                     (* (reg32 *) PinLED__PC)
/* Data Register */
#define PinLED_DR                     (* (reg32 *) PinLED__DR)
/* Input Buffer Disable Override */
#define PinLED_INP_DIS                (* (reg32 *) PinLED__PC2)


#if defined(PinLED__INTSTAT)  /* Interrupt Registers */

    #define PinLED_INTSTAT                (* (reg32 *) PinLED__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PinLED_DRIVE_MODE_SHIFT       (0x00u)
#define PinLED_DRIVE_MODE_MASK        (0x07u << PinLED_DRIVE_MODE_SHIFT)


#endif /* End Pins PinLED_H */


/* [] END OF FILE */
