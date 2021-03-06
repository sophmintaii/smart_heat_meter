/*******************************************************************************
* File Name: Pin1.h  
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

#if !defined(CY_PINS_Pin1_H) /* Pins Pin1_H */
#define CY_PINS_Pin1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin1_Write(uint8 value) ;
void    Pin1_SetDriveMode(uint8 mode) ;
uint8   Pin1_ReadDataReg(void) ;
uint8   Pin1_Read(void) ;
uint8   Pin1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin1_DRIVE_MODE_BITS        (3)
#define Pin1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin1_DRIVE_MODE_BITS))

#define Pin1_DM_ALG_HIZ         (0x00u)
#define Pin1_DM_DIG_HIZ         (0x01u)
#define Pin1_DM_RES_UP          (0x02u)
#define Pin1_DM_RES_DWN         (0x03u)
#define Pin1_DM_OD_LO           (0x04u)
#define Pin1_DM_OD_HI           (0x05u)
#define Pin1_DM_STRONG          (0x06u)
#define Pin1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin1_MASK               Pin1__MASK
#define Pin1_SHIFT              Pin1__SHIFT
#define Pin1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin1_PS                     (* (reg32 *) Pin1__PS)
/* Port Configuration */
#define Pin1_PC                     (* (reg32 *) Pin1__PC)
/* Data Register */
#define Pin1_DR                     (* (reg32 *) Pin1__DR)
/* Input Buffer Disable Override */
#define Pin1_INP_DIS                (* (reg32 *) Pin1__PC2)


#if defined(Pin1__INTSTAT)  /* Interrupt Registers */

    #define Pin1_INTSTAT                (* (reg32 *) Pin1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin1_DRIVE_MODE_SHIFT       (0x00u)
#define Pin1_DRIVE_MODE_MASK        (0x07u << Pin1_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin1_H */


/* [] END OF FILE */
