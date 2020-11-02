/*******************************************************************************
* File Name: OneWire_clock_delay.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_OneWire_clock_delay_H)
#define CY_CLOCK_OneWire_clock_delay_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void OneWire_clock_delay_StartEx(uint32 alignClkDiv);
#define OneWire_clock_delay_Start() \
    OneWire_clock_delay_StartEx(OneWire_clock_delay__PA_DIV_ID)

#else

void OneWire_clock_delay_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void OneWire_clock_delay_Stop(void);

void OneWire_clock_delay_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 OneWire_clock_delay_GetDividerRegister(void);
uint8  OneWire_clock_delay_GetFractionalDividerRegister(void);

#define OneWire_clock_delay_Enable()                         OneWire_clock_delay_Start()
#define OneWire_clock_delay_Disable()                        OneWire_clock_delay_Stop()
#define OneWire_clock_delay_SetDividerRegister(clkDivider, reset)  \
    OneWire_clock_delay_SetFractionalDividerRegister((clkDivider), 0u)
#define OneWire_clock_delay_SetDivider(clkDivider)           OneWire_clock_delay_SetDividerRegister((clkDivider), 1u)
#define OneWire_clock_delay_SetDividerValue(clkDivider)      OneWire_clock_delay_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define OneWire_clock_delay_DIV_ID     OneWire_clock_delay__DIV_ID

#define OneWire_clock_delay_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define OneWire_clock_delay_CTRL_REG   (*(reg32 *)OneWire_clock_delay__CTRL_REGISTER)
#define OneWire_clock_delay_DIV_REG    (*(reg32 *)OneWire_clock_delay__DIV_REGISTER)

#define OneWire_clock_delay_CMD_DIV_SHIFT          (0u)
#define OneWire_clock_delay_CMD_PA_DIV_SHIFT       (8u)
#define OneWire_clock_delay_CMD_DISABLE_SHIFT      (30u)
#define OneWire_clock_delay_CMD_ENABLE_SHIFT       (31u)

#define OneWire_clock_delay_CMD_DISABLE_MASK       ((uint32)((uint32)1u << OneWire_clock_delay_CMD_DISABLE_SHIFT))
#define OneWire_clock_delay_CMD_ENABLE_MASK        ((uint32)((uint32)1u << OneWire_clock_delay_CMD_ENABLE_SHIFT))

#define OneWire_clock_delay_DIV_FRAC_MASK  (0x000000F8u)
#define OneWire_clock_delay_DIV_FRAC_SHIFT (3u)
#define OneWire_clock_delay_DIV_INT_MASK   (0xFFFFFF00u)
#define OneWire_clock_delay_DIV_INT_SHIFT  (8u)

#else 

#define OneWire_clock_delay_DIV_REG        (*(reg32 *)OneWire_clock_delay__REGISTER)
#define OneWire_clock_delay_ENABLE_REG     OneWire_clock_delay_DIV_REG
#define OneWire_clock_delay_DIV_FRAC_MASK  OneWire_clock_delay__FRAC_MASK
#define OneWire_clock_delay_DIV_FRAC_SHIFT (16u)
#define OneWire_clock_delay_DIV_INT_MASK   OneWire_clock_delay__DIVIDER_MASK
#define OneWire_clock_delay_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_OneWire_clock_delay_H) */

/* [] END OF FILE */
