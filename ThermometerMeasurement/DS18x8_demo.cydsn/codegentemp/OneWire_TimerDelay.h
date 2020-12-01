/*******************************************************************************
* File Name: OneWire_TimerDelay.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_OneWire_TimerDelay_H)
#define CY_TIMER_OneWire_TimerDelay_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 OneWire_TimerDelay_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define OneWire_TimerDelay_Resolution                 16u
#define OneWire_TimerDelay_UsingFixedFunction         0u
#define OneWire_TimerDelay_UsingHWCaptureCounter      0u
#define OneWire_TimerDelay_SoftwareCaptureMode        0u
#define OneWire_TimerDelay_SoftwareTriggerMode        0u
#define OneWire_TimerDelay_UsingHWEnable              0u
#define OneWire_TimerDelay_EnableTriggerMode          1u
#define OneWire_TimerDelay_InterruptOnCaptureCount    0u
#define OneWire_TimerDelay_RunModeUsed                1u
#define OneWire_TimerDelay_ControlRegRemoved          0u

#if defined(OneWire_TimerDelay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define OneWire_TimerDelay_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (OneWire_TimerDelay_UsingFixedFunction)
    #define OneWire_TimerDelay_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define OneWire_TimerDelay_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End OneWire_TimerDelay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!OneWire_TimerDelay_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (OneWire_TimerDelay_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!OneWire_TimerDelay_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}OneWire_TimerDelay_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    OneWire_TimerDelay_Start(void) ;
void    OneWire_TimerDelay_Stop(void) ;

void    OneWire_TimerDelay_SetInterruptMode(uint8 interruptMode) ;
uint8   OneWire_TimerDelay_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define OneWire_TimerDelay_GetInterruptSource() OneWire_TimerDelay_ReadStatusRegister()

#if(!OneWire_TimerDelay_UDB_CONTROL_REG_REMOVED)
    uint8   OneWire_TimerDelay_ReadControlRegister(void) ;
    void    OneWire_TimerDelay_WriteControlRegister(uint8 control) ;
#endif /* (!OneWire_TimerDelay_UDB_CONTROL_REG_REMOVED) */

uint16  OneWire_TimerDelay_ReadPeriod(void) ;
void    OneWire_TimerDelay_WritePeriod(uint16 period) ;
uint16  OneWire_TimerDelay_ReadCounter(void) ;
void    OneWire_TimerDelay_WriteCounter(uint16 counter) ;
uint16  OneWire_TimerDelay_ReadCapture(void) ;
void    OneWire_TimerDelay_SoftwareCapture(void) ;

#if(!OneWire_TimerDelay_UsingFixedFunction) /* UDB Prototypes */
    #if (OneWire_TimerDelay_SoftwareCaptureMode)
        void    OneWire_TimerDelay_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!OneWire_TimerDelay_UsingFixedFunction) */

    #if (OneWire_TimerDelay_SoftwareTriggerMode)
        void    OneWire_TimerDelay_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (OneWire_TimerDelay_SoftwareTriggerMode) */

    #if (OneWire_TimerDelay_EnableTriggerMode)
        void    OneWire_TimerDelay_EnableTrigger(void) ;
        void    OneWire_TimerDelay_DisableTrigger(void) ;
    #endif /* (OneWire_TimerDelay_EnableTriggerMode) */


    #if(OneWire_TimerDelay_InterruptOnCaptureCount)
        void    OneWire_TimerDelay_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (OneWire_TimerDelay_InterruptOnCaptureCount) */

    #if (OneWire_TimerDelay_UsingHWCaptureCounter)
        void    OneWire_TimerDelay_SetCaptureCount(uint8 captureCount) ;
        uint8   OneWire_TimerDelay_ReadCaptureCount(void) ;
    #endif /* (OneWire_TimerDelay_UsingHWCaptureCounter) */

    void OneWire_TimerDelay_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void OneWire_TimerDelay_Init(void)          ;
void OneWire_TimerDelay_Enable(void)        ;
void OneWire_TimerDelay_SaveConfig(void)    ;
void OneWire_TimerDelay_RestoreConfig(void) ;
void OneWire_TimerDelay_Sleep(void)         ;
void OneWire_TimerDelay_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define OneWire_TimerDelay__B_TIMER__CM_NONE 0
#define OneWire_TimerDelay__B_TIMER__CM_RISINGEDGE 1
#define OneWire_TimerDelay__B_TIMER__CM_FALLINGEDGE 2
#define OneWire_TimerDelay__B_TIMER__CM_EITHEREDGE 3
#define OneWire_TimerDelay__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define OneWire_TimerDelay__B_TIMER__TM_NONE 0x00u
#define OneWire_TimerDelay__B_TIMER__TM_RISINGEDGE 0x04u
#define OneWire_TimerDelay__B_TIMER__TM_FALLINGEDGE 0x08u
#define OneWire_TimerDelay__B_TIMER__TM_EITHEREDGE 0x0Cu
#define OneWire_TimerDelay__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define OneWire_TimerDelay_INIT_PERIOD             749u
#define OneWire_TimerDelay_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << OneWire_TimerDelay_CTRL_CAP_MODE_SHIFT))
#define OneWire_TimerDelay_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << OneWire_TimerDelay_CTRL_TRIG_MODE_SHIFT))
#if (OneWire_TimerDelay_UsingFixedFunction)
    #define OneWire_TimerDelay_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << OneWire_TimerDelay_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define OneWire_TimerDelay_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << OneWire_TimerDelay_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << OneWire_TimerDelay_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (OneWire_TimerDelay_UsingFixedFunction) */
#define OneWire_TimerDelay_INIT_CAPTURE_COUNT      (2u)
#define OneWire_TimerDelay_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << OneWire_TimerDelay_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (OneWire_TimerDelay_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define OneWire_TimerDelay_STATUS         (*(reg8 *) OneWire_TimerDelay_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define OneWire_TimerDelay_STATUS_MASK    (*(reg8 *) OneWire_TimerDelay_TimerHW__SR0 )
    #define OneWire_TimerDelay_CONTROL        (*(reg8 *) OneWire_TimerDelay_TimerHW__CFG0)
    #define OneWire_TimerDelay_CONTROL2       (*(reg8 *) OneWire_TimerDelay_TimerHW__CFG1)
    #define OneWire_TimerDelay_CONTROL2_PTR   ( (reg8 *) OneWire_TimerDelay_TimerHW__CFG1)
    #define OneWire_TimerDelay_RT1            (*(reg8 *) OneWire_TimerDelay_TimerHW__RT1)
    #define OneWire_TimerDelay_RT1_PTR        ( (reg8 *) OneWire_TimerDelay_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define OneWire_TimerDelay_CONTROL3       (*(reg8 *) OneWire_TimerDelay_TimerHW__CFG2)
        #define OneWire_TimerDelay_CONTROL3_PTR   ( (reg8 *) OneWire_TimerDelay_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define OneWire_TimerDelay_GLOBAL_ENABLE  (*(reg8 *) OneWire_TimerDelay_TimerHW__PM_ACT_CFG)
    #define OneWire_TimerDelay_GLOBAL_STBY_ENABLE  (*(reg8 *) OneWire_TimerDelay_TimerHW__PM_STBY_CFG)

    #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg16 *) OneWire_TimerDelay_TimerHW__CAP0 )
    #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg16 *) OneWire_TimerDelay_TimerHW__CAP0 )
    #define OneWire_TimerDelay_PERIOD_LSB          (* (reg16 *) OneWire_TimerDelay_TimerHW__PER0 )
    #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg16 *) OneWire_TimerDelay_TimerHW__PER0 )
    #define OneWire_TimerDelay_COUNTER_LSB         (* (reg16 *) OneWire_TimerDelay_TimerHW__CNT_CMP0 )
    #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg16 *) OneWire_TimerDelay_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define OneWire_TimerDelay_BLOCK_EN_MASK                     OneWire_TimerDelay_TimerHW__PM_ACT_MSK
    #define OneWire_TimerDelay_BLOCK_STBY_EN_MASK                OneWire_TimerDelay_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define OneWire_TimerDelay_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define OneWire_TimerDelay_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define OneWire_TimerDelay_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define OneWire_TimerDelay_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define OneWire_TimerDelay_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define OneWire_TimerDelay_CTRL_ENABLE                        ((uint8)((uint8)0x01u << OneWire_TimerDelay_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define OneWire_TimerDelay_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define OneWire_TimerDelay_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << OneWire_TimerDelay_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define OneWire_TimerDelay_CTRL_MODE_SHIFT                 0x01u
        #define OneWire_TimerDelay_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << OneWire_TimerDelay_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define OneWire_TimerDelay_CTRL_RCOD_SHIFT        0x02u
        #define OneWire_TimerDelay_CTRL_ENBL_SHIFT        0x00u
        #define OneWire_TimerDelay_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define OneWire_TimerDelay_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << OneWire_TimerDelay_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define OneWire_TimerDelay_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << OneWire_TimerDelay_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define OneWire_TimerDelay_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << OneWire_TimerDelay_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define OneWire_TimerDelay_CTRL_RCOD       ((uint8)((uint8)0x03u << OneWire_TimerDelay_CTRL_RCOD_SHIFT))
        #define OneWire_TimerDelay_CTRL_ENBL       ((uint8)((uint8)0x80u << OneWire_TimerDelay_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define OneWire_TimerDelay_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define OneWire_TimerDelay_RT1_MASK                        ((uint8)((uint8)0x03u << OneWire_TimerDelay_RT1_SHIFT))
    #define OneWire_TimerDelay_SYNC                            ((uint8)((uint8)0x03u << OneWire_TimerDelay_RT1_SHIFT))
    #define OneWire_TimerDelay_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define OneWire_TimerDelay_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << OneWire_TimerDelay_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define OneWire_TimerDelay_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << OneWire_TimerDelay_SYNCDSI_SHIFT))

    #define OneWire_TimerDelay_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << OneWire_TimerDelay_CTRL_MODE_SHIFT))
    #define OneWire_TimerDelay_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << OneWire_TimerDelay_CTRL_MODE_SHIFT))
    #define OneWire_TimerDelay_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << OneWire_TimerDelay_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define OneWire_TimerDelay_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define OneWire_TimerDelay_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define OneWire_TimerDelay_STATUS_TC_INT_MASK_SHIFT        (OneWire_TimerDelay_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK_SHIFT   (OneWire_TimerDelay_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define OneWire_TimerDelay_STATUS_TC                       ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_TC_SHIFT))
    #define OneWire_TimerDelay_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define OneWire_TimerDelay_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define OneWire_TimerDelay_STATUS              (* (reg8 *) OneWire_TimerDelay_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define OneWire_TimerDelay_STATUS_MASK         (* (reg8 *) OneWire_TimerDelay_TimerUDB_rstSts_stsreg__MASK_REG)
    #define OneWire_TimerDelay_STATUS_AUX_CTRL     (* (reg8 *) OneWire_TimerDelay_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define OneWire_TimerDelay_CONTROL             (* (reg8 *) OneWire_TimerDelay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(OneWire_TimerDelay_Resolution <= 8u) /* 8-bit Timer */
        #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OneWire_TimerDelay_PERIOD_LSB          (* (reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OneWire_TimerDelay_COUNTER_LSB         (* (reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(OneWire_TimerDelay_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB          (* (reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB         (* (reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB          (* (reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB         (* (reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg16 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(OneWire_TimerDelay_Resolution <= 24u)/* 24-bit Timer */
        #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OneWire_TimerDelay_PERIOD_LSB          (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OneWire_TimerDelay_COUNTER_LSB         (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB          (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB         (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define OneWire_TimerDelay_CAPTURE_LSB         (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define OneWire_TimerDelay_CAPTURE_LSB_PTR       ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB          (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define OneWire_TimerDelay_PERIOD_LSB_PTR        ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB         (* (reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define OneWire_TimerDelay_COUNTER_LSB_PTR       ((reg32 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define OneWire_TimerDelay_COUNTER_LSB_PTR_8BIT       ((reg8 *) OneWire_TimerDelay_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (OneWire_TimerDelay_UsingHWCaptureCounter)
        #define OneWire_TimerDelay_CAP_COUNT              (*(reg8 *) OneWire_TimerDelay_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define OneWire_TimerDelay_CAP_COUNT_PTR          ( (reg8 *) OneWire_TimerDelay_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define OneWire_TimerDelay_CAPTURE_COUNT_CTRL     (*(reg8 *) OneWire_TimerDelay_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define OneWire_TimerDelay_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) OneWire_TimerDelay_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (OneWire_TimerDelay_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define OneWire_TimerDelay_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define OneWire_TimerDelay_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << OneWire_TimerDelay_CTRL_INTCNT_SHIFT))
    #define OneWire_TimerDelay_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << OneWire_TimerDelay_CTRL_TRIG_MODE_SHIFT))
    #define OneWire_TimerDelay_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << OneWire_TimerDelay_CTRL_TRIG_EN_SHIFT))
    #define OneWire_TimerDelay_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << OneWire_TimerDelay_CTRL_CAP_MODE_SHIFT))
    #define OneWire_TimerDelay_CTRL_ENABLE                    ((uint8)((uint8)0x01u << OneWire_TimerDelay_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define OneWire_TimerDelay_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define OneWire_TimerDelay_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_STATUS_TC_INT_MASK_SHIFT       OneWire_TimerDelay_STATUS_TC_SHIFT
    #define OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK_SHIFT  OneWire_TimerDelay_STATUS_CAPTURE_SHIFT
    #define OneWire_TimerDelay_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define OneWire_TimerDelay_STATUS_FIFOFULL_INT_MASK_SHIFT OneWire_TimerDelay_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define OneWire_TimerDelay_STATUS_TC                      ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define OneWire_TimerDelay_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define OneWire_TimerDelay_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define OneWire_TimerDelay_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define OneWire_TimerDelay_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define OneWire_TimerDelay_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define OneWire_TimerDelay_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << OneWire_TimerDelay_STATUS_FIFOFULL_SHIFT))

    #define OneWire_TimerDelay_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define OneWire_TimerDelay_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define OneWire_TimerDelay_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define OneWire_TimerDelay_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define OneWire_TimerDelay_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define OneWire_TimerDelay_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_OneWire_TimerDelay_H */


/* [] END OF FILE */
