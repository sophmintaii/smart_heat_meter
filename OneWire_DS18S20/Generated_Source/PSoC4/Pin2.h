/*******************************************************************************
* File Name: Pin2.h  
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

#if !defined(CY_PINS_Pin2_H) /* Pins Pin2_H */
#define CY_PINS_Pin2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin2_Write(uint8 value) ;
void    Pin2_SetDriveMode(uint8 mode) ;
uint8   Pin2_ReadDataReg(void) ;
uint8   Pin2_Read(void) ;
uint8   Pin2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin2_DRIVE_MODE_BITS        (3)
#define Pin2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin2_DRIVE_MODE_BITS))

#define Pin2_DM_ALG_HIZ         (0x00u)
#define Pin2_DM_DIG_HIZ         (0x01u)
#define Pin2_DM_RES_UP          (0x02u)
#define Pin2_DM_RES_DWN         (0x03u)
#define Pin2_DM_OD_LO           (0x04u)
#define Pin2_DM_OD_HI           (0x05u)
#define Pin2_DM_STRONG          (0x06u)
#define Pin2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Pin2_MASK               Pin2__MASK
#define Pin2_SHIFT              Pin2__SHIFT
#define Pin2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin2_PS                     (* (reg32 *) Pin2__PS)
/* Port Configuration */
#define Pin2_PC                     (* (reg32 *) Pin2__PC)
/* Data Register */
#define Pin2_DR                     (* (reg32 *) Pin2__DR)
/* Input Buffer Disable Override */
#define Pin2_INP_DIS                (* (reg32 *) Pin2__PC2)


#if defined(Pin2__INTSTAT)  /* Interrupt Registers */

    #define Pin2_INTSTAT                (* (reg32 *) Pin2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Pin2_DRIVE_MODE_SHIFT       (0x00u)
#define Pin2_DRIVE_MODE_MASK        (0x07u << Pin2_DRIVE_MODE_SHIFT)


#endif /* End Pins Pin2_H */


/* [] END OF FILE */
