/*******************************************************************************
* File Name: OneWire_isr_DataReady.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_OneWire_isr_DataReady_H)
#define CY_ISR_OneWire_isr_DataReady_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void OneWire_isr_DataReady_Start(void);
void OneWire_isr_DataReady_StartEx(cyisraddress address);
void OneWire_isr_DataReady_Stop(void);

CY_ISR_PROTO(OneWire_isr_DataReady_Interrupt);

void OneWire_isr_DataReady_SetVector(cyisraddress address);
cyisraddress OneWire_isr_DataReady_GetVector(void);

void OneWire_isr_DataReady_SetPriority(uint8 priority);
uint8 OneWire_isr_DataReady_GetPriority(void);

void OneWire_isr_DataReady_Enable(void);
uint8 OneWire_isr_DataReady_GetState(void);
void OneWire_isr_DataReady_Disable(void);

void OneWire_isr_DataReady_SetPending(void);
void OneWire_isr_DataReady_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the OneWire_isr_DataReady ISR. */
#define OneWire_isr_DataReady_INTC_VECTOR            ((reg32 *) OneWire_isr_DataReady__INTC_VECT)

/* Address of the OneWire_isr_DataReady ISR priority. */
#define OneWire_isr_DataReady_INTC_PRIOR             ((reg32 *) OneWire_isr_DataReady__INTC_PRIOR_REG)

/* Priority of the OneWire_isr_DataReady interrupt. */
#define OneWire_isr_DataReady_INTC_PRIOR_NUMBER      OneWire_isr_DataReady__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable OneWire_isr_DataReady interrupt. */
#define OneWire_isr_DataReady_INTC_SET_EN            ((reg32 *) OneWire_isr_DataReady__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the OneWire_isr_DataReady interrupt. */
#define OneWire_isr_DataReady_INTC_CLR_EN            ((reg32 *) OneWire_isr_DataReady__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the OneWire_isr_DataReady interrupt state to pending. */
#define OneWire_isr_DataReady_INTC_SET_PD            ((reg32 *) OneWire_isr_DataReady__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the OneWire_isr_DataReady interrupt. */
#define OneWire_isr_DataReady_INTC_CLR_PD            ((reg32 *) OneWire_isr_DataReady__INTC_CLR_PD_REG)



#endif /* CY_ISR_OneWire_isr_DataReady_H */


/* [] END OF FILE */
