/*******************************************************************************
* File Name: Pin_22.h  
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

#if !defined(CY_PINS_Pin_22_H) /* Pins Pin_22_H */
#define CY_PINS_Pin_22_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_22_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_22_Write(uint8 value) ;
void    Pin_22_SetDriveMode(uint8 mode) ;
uint8   Pin_22_ReadDataReg(void) ;
uint8   Pin_22_Read(void) ;
uint8   Pin_22_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_22_DRIVE_MODE_BITS        (3)
#define Pin_22_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_22_DRIVE_MODE_BITS))

#define Pin_22_DM_ALG_HIZ         (0x00u)
#define Pin_22_DM_DIG_HIZ         (0x01u)
#define Pin_22_DM_RES_UP          (0x02u)
#define Pin_22_DM_RES_DWN         (0x03u)
#define Pin_22_DM_OD_LO           (0x04u)
#define Pin_22_DM_OD_HI           (0x05u)
#define Pin_22_DM_STRONG          (0x06u)
#define Pin_22_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin_22_MASK               Pin_22__MASK
#define Pin_22_SHIFT              Pin_22__SHIFT
#define Pin_22_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_22_PS                     (* (reg32 *) Pin_22__PS)
/* Port Configuration */
#define Pin_22_PC                     (* (reg32 *) Pin_22__PC)
/* Data Register */
#define Pin_22_DR                     (* (reg32 *) Pin_22__DR)
/* Input Buffer Disable Override */
#define Pin_22_INP_DIS                (* (reg32 *) Pin_22__PC2)


#if defined(Pin_22__INTSTAT)  /* Interrupt Registers */

    #define Pin_22_INTSTAT                (* (reg32 *) Pin_22__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin_22_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_22_DRIVE_MODE_MASK        (0x07u << Pin_22_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin_22_H */


/* [] END OF FILE */
