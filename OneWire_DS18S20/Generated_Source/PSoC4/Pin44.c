/*******************************************************************************
* File Name: Pin44.c  
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
#include "Pin44.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pin44_PC =   (Pin44_PC & \
                                (uint32)(~(uint32)(Pin44_DRIVE_MODE_IND_MASK << (Pin44_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pin44_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pin44_Write
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
void Pin44_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pin44_DR & (uint8)(~Pin44_MASK));
    drVal = (drVal | ((uint8)(value << Pin44_SHIFT) & Pin44_MASK));
    Pin44_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pin44_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin44_DM_STRONG     Strong Drive 
*  Pin44_DM_OD_HI      Open Drain, Drives High 
*  Pin44_DM_OD_LO      Open Drain, Drives Low 
*  Pin44_DM_RES_UP     Resistive Pull Up 
*  Pin44_DM_RES_DWN    Resistive Pull Down 
*  Pin44_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin44_DM_DIG_HIZ    High Impedance Digital 
*  Pin44_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin44_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pin44__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pin44_Read
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
*  Macro Pin44_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin44_Read(void) 
{
    return (uint8)((Pin44_PS & Pin44_MASK) >> Pin44_SHIFT);
}


/*******************************************************************************
* Function Name: Pin44_ReadDataReg
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
uint8 Pin44_ReadDataReg(void) 
{
    return (uint8)((Pin44_DR & Pin44_MASK) >> Pin44_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin44_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin44_ClearInterrupt
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
    uint8 Pin44_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pin44_INTSTAT & Pin44_MASK);
		Pin44_INTSTAT = maskedStatus;
        return maskedStatus >> Pin44_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
