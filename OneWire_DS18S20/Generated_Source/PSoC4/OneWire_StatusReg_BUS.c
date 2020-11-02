/*******************************************************************************
* File Name: OneWire_StatusReg_BUS.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "OneWire_StatusReg_BUS.h"

#if !defined(OneWire_StatusReg_BUS_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: OneWire_StatusReg_BUS_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 OneWire_StatusReg_BUS_Read(void) 
{ 
    return OneWire_StatusReg_BUS_Status;
}


/*******************************************************************************
* Function Name: OneWire_StatusReg_BUS_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void OneWire_StatusReg_BUS_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    OneWire_StatusReg_BUS_Status_Aux_Ctrl |= OneWire_StatusReg_BUS_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: OneWire_StatusReg_BUS_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void OneWire_StatusReg_BUS_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    OneWire_StatusReg_BUS_Status_Aux_Ctrl &= (uint8)(~OneWire_StatusReg_BUS_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: OneWire_StatusReg_BUS_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void OneWire_StatusReg_BUS_WriteMask(uint8 mask) 
{
    #if(OneWire_StatusReg_BUS_INPUTS < 8u)
    	mask &= (uint8)((((uint8)1u) << OneWire_StatusReg_BUS_INPUTS) - 1u);
	#endif /* End OneWire_StatusReg_BUS_INPUTS < 8u */
    OneWire_StatusReg_BUS_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: OneWire_StatusReg_BUS_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 OneWire_StatusReg_BUS_ReadMask(void) 
{
    return OneWire_StatusReg_BUS_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
