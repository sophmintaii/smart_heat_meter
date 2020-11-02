/*******************************************************************************
* File Name: OneWire_StatusReg_BUS.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_OneWire_StatusReg_BUS_H) /* CY_STATUS_REG_OneWire_StatusReg_BUS_H */
#define CY_STATUS_REG_OneWire_StatusReg_BUS_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 OneWire_StatusReg_BUS_Read(void) ;
void OneWire_StatusReg_BUS_InterruptEnable(void) ;
void OneWire_StatusReg_BUS_InterruptDisable(void) ;
void OneWire_StatusReg_BUS_WriteMask(uint8 mask) ;
uint8 OneWire_StatusReg_BUS_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define OneWire_StatusReg_BUS_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define OneWire_StatusReg_BUS_INPUTS              8


/***************************************
*             Registers
***************************************/

/* Status Register */
#define OneWire_StatusReg_BUS_Status             (* (reg8 *) OneWire_StatusReg_BUS_sts_sts_reg__STATUS_REG )
#define OneWire_StatusReg_BUS_Status_PTR         (  (reg8 *) OneWire_StatusReg_BUS_sts_sts_reg__STATUS_REG )
#define OneWire_StatusReg_BUS_Status_Mask        (* (reg8 *) OneWire_StatusReg_BUS_sts_sts_reg__MASK_REG )
#define OneWire_StatusReg_BUS_Status_Aux_Ctrl    (* (reg8 *) OneWire_StatusReg_BUS_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_OneWire_StatusReg_BUS_H */


/* [] END OF FILE */
