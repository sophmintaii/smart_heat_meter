/*******************************************************************************
* File Name: Pin44.h  
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

#if !defined(CY_PINS_Pin44_H) /* Pins Pin44_H */
#define CY_PINS_Pin44_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin44_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin44_Write(uint8 value) ;
void    Pin44_SetDriveMode(uint8 mode) ;
uint8   Pin44_ReadDataReg(void) ;
uint8   Pin44_Read(void) ;
uint8   Pin44_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin44_DRIVE_MODE_BITS        (3)
#define Pin44_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin44_DRIVE_MODE_BITS))

#define Pin44_DM_ALG_HIZ         (0x00u)
#define Pin44_DM_DIG_HIZ         (0x01u)
#define Pin44_DM_RES_UP          (0x02u)
#define Pin44_DM_RES_DWN         (0x03u)
#define Pin44_DM_OD_LO           (0x04u)
#define Pin44_DM_OD_HI           (0x05u)
#define Pin44_DM_STRONG          (0x06u)
#define Pin44_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin44_MASK               Pin44__MASK
#define Pin44_SHIFT              Pin44__SHIFT
#define Pin44_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin44_PS                     (* (reg32 *) Pin44__PS)
/* Port Configuration */
#define Pin44_PC                     (* (reg32 *) Pin44__PC)
/* Data Register */
#define Pin44_DR                     (* (reg32 *) Pin44__DR)
/* Input Buffer Disable Override */
#define Pin44_INP_DIS                (* (reg32 *) Pin44__PC2)


#if defined(Pin44__INTSTAT)  /* Interrupt Registers */

    #define Pin44_INTSTAT                (* (reg32 *) Pin44__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin44_DRIVE_MODE_SHIFT       (0x00u)
#define Pin44_DRIVE_MODE_MASK        (0x07u << Pin44_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin44_H */


/* [] END OF FILE */
