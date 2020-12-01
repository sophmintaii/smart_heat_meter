/*******************************************************************************
* File Name: Pin0.h  
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

#if !defined(CY_PINS_Pin0_H) /* Pins Pin0_H */
#define CY_PINS_Pin0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin0_Write(uint8 value) ;
void    Pin0_SetDriveMode(uint8 mode) ;
uint8   Pin0_ReadDataReg(void) ;
uint8   Pin0_Read(void) ;
uint8   Pin0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin0_DRIVE_MODE_BITS        (3)
#define Pin0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin0_DRIVE_MODE_BITS))

#define Pin0_DM_ALG_HIZ         (0x00u)
#define Pin0_DM_DIG_HIZ         (0x01u)
#define Pin0_DM_RES_UP          (0x02u)
#define Pin0_DM_RES_DWN         (0x03u)
#define Pin0_DM_OD_LO           (0x04u)
#define Pin0_DM_OD_HI           (0x05u)
#define Pin0_DM_STRONG          (0x06u)
#define Pin0_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin0_MASK               Pin0__MASK
#define Pin0_SHIFT              Pin0__SHIFT
#define Pin0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin0_PS                     (* (reg32 *) Pin0__PS)
/* Port Configuration */
#define Pin0_PC                     (* (reg32 *) Pin0__PC)
/* Data Register */
#define Pin0_DR                     (* (reg32 *) Pin0__DR)
/* Input Buffer Disable Override */
#define Pin0_INP_DIS                (* (reg32 *) Pin0__PC2)


#if defined(Pin0__INTSTAT)  /* Interrupt Registers */

    #define Pin0_INTSTAT                (* (reg32 *) Pin0__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin0_DRIVE_MODE_SHIFT       (0x00u)
#define Pin0_DRIVE_MODE_MASK        (0x07u << Pin0_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin0_H */


/* [] END OF FILE */
