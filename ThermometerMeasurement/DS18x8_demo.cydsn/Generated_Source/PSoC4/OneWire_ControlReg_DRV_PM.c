/*******************************************************************************
* File Name: OneWire_ControlReg_DRV_PM.c
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

#include "OneWire_ControlReg_DRV.h"

/* Check for removal by optimization */
#if !defined(OneWire_ControlReg_DRV_Sync_ctrl_reg__REMOVED)

static OneWire_ControlReg_DRV_BACKUP_STRUCT  OneWire_ControlReg_DRV_backup = {0u};

    
/*******************************************************************************
* Function Name: OneWire_ControlReg_DRV_SaveConfig
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
void OneWire_ControlReg_DRV_SaveConfig(void) 
{
    OneWire_ControlReg_DRV_backup.controlState = OneWire_ControlReg_DRV_Control;
}


/*******************************************************************************
* Function Name: OneWire_ControlReg_DRV_RestoreConfig
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
void OneWire_ControlReg_DRV_RestoreConfig(void) 
{
     OneWire_ControlReg_DRV_Control = OneWire_ControlReg_DRV_backup.controlState;
}


/*******************************************************************************
* Function Name: OneWire_ControlReg_DRV_Sleep
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
void OneWire_ControlReg_DRV_Sleep(void) 
{
    OneWire_ControlReg_DRV_SaveConfig();
}


/*******************************************************************************
* Function Name: OneWire_ControlReg_DRV_Wakeup
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
void OneWire_ControlReg_DRV_Wakeup(void)  
{
    OneWire_ControlReg_DRV_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
