/*******************************************************************************
* File Name: GREEN_LED_Pin.h  
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

#if !defined(CY_PINS_GREEN_LED_Pin_H) /* Pins GREEN_LED_Pin_H */
#define CY_PINS_GREEN_LED_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GREEN_LED_Pin_aliases.h"


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
} GREEN_LED_Pin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GREEN_LED_Pin_Read(void);
void    GREEN_LED_Pin_Write(uint8 value);
uint8   GREEN_LED_Pin_ReadDataReg(void);
#if defined(GREEN_LED_Pin__PC) || (CY_PSOC4_4200L) 
    void    GREEN_LED_Pin_SetDriveMode(uint8 mode);
#endif
void    GREEN_LED_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   GREEN_LED_Pin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GREEN_LED_Pin_Sleep(void); 
void GREEN_LED_Pin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GREEN_LED_Pin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GREEN_LED_Pin_DRIVE_MODE_BITS        (3)
    #define GREEN_LED_Pin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GREEN_LED_Pin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GREEN_LED_Pin_SetDriveMode() function.
         *  @{
         */
        #define GREEN_LED_Pin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GREEN_LED_Pin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GREEN_LED_Pin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GREEN_LED_Pin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GREEN_LED_Pin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GREEN_LED_Pin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GREEN_LED_Pin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GREEN_LED_Pin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GREEN_LED_Pin_MASK               GREEN_LED_Pin__MASK
#define GREEN_LED_Pin_SHIFT              GREEN_LED_Pin__SHIFT
#define GREEN_LED_Pin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GREEN_LED_Pin_SetInterruptMode() function.
     *  @{
     */
        #define GREEN_LED_Pin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GREEN_LED_Pin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GREEN_LED_Pin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GREEN_LED_Pin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GREEN_LED_Pin__SIO)
    #define GREEN_LED_Pin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GREEN_LED_Pin__PC) && (CY_PSOC4_4200L)
    #define GREEN_LED_Pin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GREEN_LED_Pin_USBIO_DISABLE              ((uint32)(~GREEN_LED_Pin_USBIO_ENABLE))
    #define GREEN_LED_Pin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GREEN_LED_Pin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GREEN_LED_Pin_USBIO_ENTER_SLEEP          ((uint32)((1u << GREEN_LED_Pin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GREEN_LED_Pin_USBIO_SUSPEND_DEL_SHIFT)))
    #define GREEN_LED_Pin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GREEN_LED_Pin_USBIO_SUSPEND_SHIFT)))
    #define GREEN_LED_Pin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GREEN_LED_Pin_USBIO_SUSPEND_DEL_SHIFT)))
    #define GREEN_LED_Pin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GREEN_LED_Pin__PC)
    /* Port Configuration */
    #define GREEN_LED_Pin_PC                 (* (reg32 *) GREEN_LED_Pin__PC)
#endif
/* Pin State */
#define GREEN_LED_Pin_PS                     (* (reg32 *) GREEN_LED_Pin__PS)
/* Data Register */
#define GREEN_LED_Pin_DR                     (* (reg32 *) GREEN_LED_Pin__DR)
/* Input Buffer Disable Override */
#define GREEN_LED_Pin_INP_DIS                (* (reg32 *) GREEN_LED_Pin__PC2)

/* Interrupt configuration Registers */
#define GREEN_LED_Pin_INTCFG                 (* (reg32 *) GREEN_LED_Pin__INTCFG)
#define GREEN_LED_Pin_INTSTAT                (* (reg32 *) GREEN_LED_Pin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GREEN_LED_Pin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GREEN_LED_Pin__SIO)
    #define GREEN_LED_Pin_SIO_REG            (* (reg32 *) GREEN_LED_Pin__SIO)
#endif /* (GREEN_LED_Pin__SIO_CFG) */

/* USBIO registers */
#if !defined(GREEN_LED_Pin__PC) && (CY_PSOC4_4200L)
    #define GREEN_LED_Pin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GREEN_LED_Pin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GREEN_LED_Pin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GREEN_LED_Pin_DRIVE_MODE_SHIFT       (0x00u)
#define GREEN_LED_Pin_DRIVE_MODE_MASK        (0x07u << GREEN_LED_Pin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GREEN_LED_Pin_H */


/* [] END OF FILE */
