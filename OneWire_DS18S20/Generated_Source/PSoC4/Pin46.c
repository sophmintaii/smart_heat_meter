/*******************************************************************************
* File Name: Pin46.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Pin46.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pin46_PC =   (Pin46_PC & \
                                (uint32)(~(uint32)(Pin46_DRIVE_MODE_IND_MASK << (Pin46_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pin46_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pin46_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Pin46_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pin46_DR & (uint8)(~Pin46_MASK));
    drVal = (drVal | ((uint8)(value << Pin46_SHIFT) & Pin46_MASK));
    Pin46_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pin46_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin46_DM_STRONG     Strong Drive 
*  Pin46_DM_OD_HI      Open Drain, Drives High 
*  Pin46_DM_OD_LO      Open Drain, Drives Low 
*  Pin46_DM_RES_UP     Resistive Pull Up 
*  Pin46_DM_RES_DWN    Resistive Pull Down 
*  Pin46_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin46_DM_DIG_HIZ    High Impedance Digital 
*  Pin46_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin46_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pin46__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pin46_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Pin46_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin46_Read(void) 
{
    return (uint8)((Pin46_PS & Pin46_MASK) >> Pin46_SHIFT);
}


/*******************************************************************************
* Function Name: Pin46_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Pin46_ReadDataReg(void) 
{
    return (uint8)((Pin46_DR & Pin46_MASK) >> Pin46_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin46_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin46_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Pin46_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pin46_INTSTAT & Pin46_MASK);
		Pin46_INTSTAT = maskedStatus;
        return maskedStatus >> Pin46_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
