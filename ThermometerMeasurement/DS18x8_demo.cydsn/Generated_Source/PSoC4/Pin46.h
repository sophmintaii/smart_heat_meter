/*******************************************************************************
* File Name: Pin46.h  
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

#if !defined(CY_PINS_Pin46_H) /* Pins Pin46_H */
#define CY_PINS_Pin46_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin46_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin46_Write(uint8 value) ;
void    Pin46_SetDriveMode(uint8 mode) ;
uint8   Pin46_ReadDataReg(void) ;
uint8   Pin46_Read(void) ;
uint8   Pin46_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin46_DRIVE_MODE_BITS        (3)
#define Pin46_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin46_DRIVE_MODE_BITS))

#define Pin46_DM_ALG_HIZ         (0x00u)
#define Pin46_DM_DIG_HIZ         (0x01u)
#define Pin46_DM_RES_UP          (0x02u)
#define Pin46_DM_RES_DWN         (0x03u)
#define Pin46_DM_OD_LO           (0x04u)
#define Pin46_DM_OD_HI           (0x05u)
#define Pin46_DM_STRONG          (0x06u)
#define Pin46_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin46_MASK               Pin46__MASK
#define Pin46_SHIFT              Pin46__SHIFT
#define Pin46_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin46_PS                     (* (reg32 *) Pin46__PS)
/* Port Configuration */
#define Pin46_PC                     (* (reg32 *) Pin46__PC)
/* Data Register */
#define Pin46_DR                     (* (reg32 *) Pin46__DR)
/* Input Buffer Disable Override */
#define Pin46_INP_DIS                (* (reg32 *) Pin46__PC2)


#if defined(Pin46__INTSTAT)  /* Interrupt Registers */

    #define Pin46_INTSTAT                (* (reg32 *) Pin46__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin46_DRIVE_MODE_SHIFT       (0x00u)
#define Pin46_DRIVE_MODE_MASK        (0x07u << Pin46_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin46_H */


/* [] END OF FILE */
