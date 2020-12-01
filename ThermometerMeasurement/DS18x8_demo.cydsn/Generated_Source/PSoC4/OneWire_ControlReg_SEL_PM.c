/*******************************************************************************
* File Name: OneWire_ControlReg_SEL_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "OneWire_ControlReg_SEL.h"

/* Check for removal by optimization */
#if !defined(OneWire_ControlReg_SEL_Sync_ctrl_reg__REMOVED)

static OneWire_ControlReg_SEL_BACKUP_STRUCT  OneWire_ControlReg_SEL_backup = {0u};

    
/*******************************************************************************
* Function Name: OneWire_ControlReg_SEL_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void OneWire_ControlReg_SEL_SaveConfig(void) 
{
    OneWire_ControlReg_SEL_backup.controlState = OneWire_ControlReg_SEL_Control;
}


/*******************************************************************************
* Function Name: OneWire_ControlReg_SEL_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void OneWire_ControlReg_SEL_RestoreConfig(void) 
{
     OneWire_ControlReg_SEL_Control = OneWire_ControlReg_SEL_backup.controlState;
}


/*******************************************************************************
* Function Name: OneWire_ControlReg_SEL_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void OneWire_ControlReg_SEL_Sleep(void) 
{
    OneWire_ControlReg_SEL_SaveConfig();
}


/*******************************************************************************
* Function Name: OneWire_ControlReg_SEL_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void OneWire_ControlReg_SEL_Wakeup(void)  
{
    OneWire_ControlReg_SEL_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
