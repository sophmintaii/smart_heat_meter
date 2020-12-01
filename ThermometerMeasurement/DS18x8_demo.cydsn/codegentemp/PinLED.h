/*******************************************************************************
* File Name: PinLED.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PinLED_H) /* Pins PinLED_H */
#define CY_PINS_PinLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinLED_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PinLED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinLED_Read(void);
void    PinLED_Write(uint8 value);
uint8   PinLED_ReadDataReg(void);
#if defined(PinLED__PC) || (CY_PSOC4_4200L) 
    void    PinLED_SetDriveMode(uint8 mode);
#endif
void    PinLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinLED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinLED_Sleep(void); 
void PinLED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinLED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinLED_DRIVE_MODE_BITS        (3)
    #define PinLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinLED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinLED_SetDriveMode() function.
         *  @{
         */
        #define PinLED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinLED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinLED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinLED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinLED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinLED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinLED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinLED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinLED_MASK               PinLED__MASK
#define PinLED_SHIFT              PinLED__SHIFT
#define PinLED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinLED_SetInterruptMode() function.
     *  @{
     */
        #define PinLED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinLED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinLED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinLED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinLED__SIO)
    #define PinLED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinLED__PC) && (CY_PSOC4_4200L)
    #define PinLED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinLED_USBIO_DISABLE              ((uint32)(~PinLED_USBIO_ENABLE))
    #define PinLED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinLED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinLED_USBIO_ENTER_SLEEP          ((uint32)((1u << PinLED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinLED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinLED_USBIO_SUSPEND_SHIFT)))
    #define PinLED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinLED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinLED__PC)
    /* Port Configuration */
    #define PinLED_PC                 (* (reg32 *) PinLED__PC)
#endif
/* Pin State */
#define PinLED_PS                     (* (reg32 *) PinLED__PS)
/* Data Register */
#define PinLED_DR                     (* (reg32 *) PinLED__DR)
/* Input Buffer Disable Override */
#define PinLED_INP_DIS                (* (reg32 *) PinLED__PC2)

/* Interrupt configuration Registers */
#define PinLED_INTCFG                 (* (reg32 *) PinLED__INTCFG)
#define PinLED_INTSTAT                (* (reg32 *) PinLED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinLED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinLED__SIO)
    #define PinLED_SIO_REG            (* (reg32 *) PinLED__SIO)
#endif /* (PinLED__SIO_CFG) */

/* USBIO registers */
#if !defined(PinLED__PC) && (CY_PSOC4_4200L)
    #define PinLED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinLED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinLED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinLED_DRIVE_MODE_SHIFT       (0x00u)
#define PinLED_DRIVE_MODE_MASK        (0x07u << PinLED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinLED_H */


/* [] END OF FILE */
