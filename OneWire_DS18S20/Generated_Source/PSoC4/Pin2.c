/*******************************************************************************
* File Name: Pin2.c  
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
#include "Pin2.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pin2_PC =   (Pin2_PC & \
                                (uint32)(~(uint32)(Pin2_DRIVE_MODE_IND_MASK << (Pin2_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pin2_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pin2_Write
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
void Pin2_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pin2_DR & (uint8)(~Pin2_MASK));
    drVal = (drVal | ((uint8)(value << Pin2_SHIFT) & Pin2_MASK));
    Pin2_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pin2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin2_DM_STRONG     Strong Drive 
*  Pin2_DM_OD_HI      Open Drain, Drives High 
*  Pin2_DM_OD_LO      Open Drain, Drives Low 
*  Pin2_DM_RES_UP     Resistive Pull Up 
*  Pin2_DM_RES_DWN    Resistive Pull Down 
*  Pin2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin2_DM_DIG_HIZ    High Impedance Digital 
*  Pin2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin2_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pin2__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pin2_Read
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
*  Macro Pin2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin2_Read(void) 
{
    return (uint8)((Pin2_PS & Pin2_MASK) >> Pin2_SHIFT);
}


/*******************************************************************************
* Function Name: Pin2_ReadDataReg
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
uint8 Pin2_ReadDataReg(void) 
{
    return (uint8)((Pin2_DR & Pin2_MASK) >> Pin2_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin2_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin2_ClearInterrupt
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
    uint8 Pin2_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pin2_INTSTAT & Pin2_MASK);
		Pin2_INTSTAT = maskedStatus;
        return maskedStatus >> Pin2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
