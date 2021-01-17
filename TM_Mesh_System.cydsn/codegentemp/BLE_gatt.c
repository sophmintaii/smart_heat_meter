/***************************************************************************//**
* \file CYBLE_gatt.c
* \version 3.66
* 
* \brief
*  This file contains the source code for the GATT API of the BLE Component.
* 
********************************************************************************
* \copyright
* Copyright 2014-2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "BLE_eventHandler.h"


/***************************************
* Global variables
***************************************/

CYBLE_STATE_T cyBle_state;

#if ((CYBLE_MODE_PROFILE) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
    
#if(CYBLE_MODE_PROFILE)
    #if defined(__ARMCC_VERSION)
        CY_ALIGN(CYDEV_FLS_ROW_SIZE) const CY_BLE_FLASH_STORAGE cyBle_flashStorage CY_SECTION(".cy_checksum_exclude") =
    #elif defined (__GNUC__)
        const CY_BLE_FLASH_STORAGE cyBle_flashStorage CY_SECTION(".cy_checksum_exclude")
            CY_ALIGN(CYDEV_FLS_ROW_SIZE) =
    #elif defined (__ICCARM__)
        #pragma data_alignment=CY_FLASH_SIZEOF_ROW
        #pragma location=".cy_checksum_exclude"
        const CY_BLE_FLASH_STORAGE cyBle_flashStorage =
    #endif  /* (__ARMCC_VERSION) */
    {
        { 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u }, 
        {{
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        }}, 
        0x08u, /* CYBLE_GATT_DB_CCCD_COUNT */ 
        0x05u, /* CYBLE_GAP_MAX_BONDED_DEVICE */ 
    };
#endif /* (CYBLE_MODE_PROFILE) */

#endif  /* (CYBLE_MODE_PROFILE) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */

#if(CYBLE_GATT_ROLE_SERVER)
    
    const CYBLE_GATTS_T cyBle_gatts =
{
    0x000Cu,    /* Handle of the GATT service */
    0x000Eu,    /* Handle of the Service Changed characteristic */
    0x000Fu,    /* Handle of the Client Characteristic Configuration descriptor */
};
    
    static uint8 cyBle_attValues[0x40u] = {
    /* Device Name */
    (uint8)'M', (uint8)'y', (uint8)'T', (uint8)'h', (uint8)'e', (uint8)'r', (uint8)'m', (uint8)'o', (uint8)'m',
    (uint8)'e', (uint8)'t', (uint8)'e', (uint8)'r',

    /* Appearance */
    0x00u, 0x03u,

    /* Peripheral Preferred Connection Parameters */
    0x06u, 0x00u, 0x28u, 0x00u, 0x00u, 0x00u, 0xE8u, 0x03u,

    /* Central Address Resolution */
    0x00u,

    /* Resolvable Private Address Only */
    0x00u,

    /* Service Changed */
    0x00u, 0x00u, 0x00u, 0x00u,

    /* Custom Characteristic */
    0x00u,

    /* Custom Descriptor */
    0x00u, 0xB4u, 0x85u, 0x0Eu, 0x0Au, 0xEFu, 0x7Au, 0x87u, 0x9Cu, 0x33u, 0x47u, 0xE5u, 0x56u, 0x45u, 0xA6u, 0xD0u,
    0xFCu,

    /* Temperature Measurement */
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

    /* Temperature Type */
    0x01u,

    /* Intermediate Temperature */
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

    /* Measurement Interval */
    0x00u, 0x00u,

    /* Valid Range */
    0x00u, 0x00u, 0xFFu, 0xFFu,

};
#if(CYBLE_GATT_DB_CCCD_COUNT != 0u)
uint8 cyBle_attValuesCCCD[CYBLE_GATT_DB_CCCD_COUNT];
#endif /* CYBLE_GATT_DB_CCCD_COUNT != 0u */

const uint8 cyBle_attUuid128[][16u] = {
    /* Custom Service */
    { 0x97u, 0x1Bu, 0xD9u, 0x52u, 0xFEu, 0xE9u, 0xD5u, 0xBEu, 0xCFu, 0x4Eu, 0x94u, 0x05u, 0x54u, 0x56u, 0x3Au, 0x5Bu },
    /* Custom Characteristic */
    { 0xDDu, 0x94u, 0x78u, 0x38u, 0x70u, 0xECu, 0x64u, 0xB7u, 0x8Eu, 0x42u, 0xCAu, 0x18u, 0x63u, 0x73u, 0x96u, 0xA4u },
};

CYBLE_GATTS_ATT_GEN_VAL_LEN_T cyBle_attValuesLen[CYBLE_GATT_DB_ATT_VAL_COUNT] = {
    { 0x000Du, (void *)&cyBle_attValues[0] }, /* Device Name */
    { 0x0002u, (void *)&cyBle_attValues[13] }, /* Appearance */
    { 0x0008u, (void *)&cyBle_attValues[15] }, /* Peripheral Preferred Connection Parameters */
    { 0x0001u, (void *)&cyBle_attValues[23] }, /* Central Address Resolution */
    { 0x0001u, (void *)&cyBle_attValues[24] }, /* Resolvable Private Address Only */
    { 0x0004u, (void *)&cyBle_attValues[25] }, /* Service Changed */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[0] }, /* Client Characteristic Configuration */
    { 0x0010u, (void *)&cyBle_attUuid128[0] }, /* Custom Service UUID */
    { 0x0010u, (void *)&cyBle_attUuid128[1] }, /* Custom Characteristic UUID */
    { 0x0001u, (void *)&cyBle_attValues[29] }, /* Custom Characteristic */
    { 0x0001u, (void *)&cyBle_attValues[30] }, /* Custom Descriptor */
    { 0x0005u, (void *)&cyBle_attValues[47] }, /* Temperature Measurement */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[2] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[52] }, /* Temperature Type */
    { 0x0005u, (void *)&cyBle_attValues[53] }, /* Intermediate Temperature */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[4] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[58] }, /* Measurement Interval */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[6] }, /* Client Characteristic Configuration */
    { 0x0004u, (void *)&cyBle_attValues[60] }, /* Valid Range */
};

const CYBLE_GATTS_DB_T cyBle_gattDB[0x20u] = {
    { 0x0001u, 0x2800u /* Primary service                     */, 0x00000001u /*       */, 0x000Bu, {{0x1800u, NULL}}                           },
    { 0x0002u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x0003u, {{0x2A00u, NULL}}                           },
    { 0x0003u, 0x2A00u /* Device Name                         */, 0x01020001u /* rd    */, 0x0003u, {{0x000Du, (void *)&cyBle_attValuesLen[0]}} },
    { 0x0004u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x0005u, {{0x2A01u, NULL}}                           },
    { 0x0005u, 0x2A01u /* Appearance                          */, 0x01020001u /* rd    */, 0x0005u, {{0x0002u, (void *)&cyBle_attValuesLen[1]}} },
    { 0x0006u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x0007u, {{0x2A04u, NULL}}                           },
    { 0x0007u, 0x2A04u /* Peripheral Preferred Connection Par */, 0x01020001u /* rd    */, 0x0007u, {{0x0008u, (void *)&cyBle_attValuesLen[2]}} },
    { 0x0008u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x0009u, {{0x2AA6u, NULL}}                           },
    { 0x0009u, 0x2AA6u /* Central Address Resolution          */, 0x01020001u /* rd    */, 0x0009u, {{0x0001u, (void *)&cyBle_attValuesLen[3]}} },
    { 0x000Au, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x000Bu, {{0x2AC9u, NULL}}                           },
    { 0x000Bu, 0x2AC9u /* Resolvable Private Address Only     */, 0x01020001u /* rd    */, 0x000Bu, {{0x0001u, (void *)&cyBle_attValuesLen[4]}} },
    { 0x000Cu, 0x2800u /* Primary service                     */, 0x00000001u /*       */, 0x000Fu, {{0x1801u, NULL}}                           },
    { 0x000Du, 0x2803u /* Characteristic                      */, 0x00200001u /* ind   */, 0x000Fu, {{0x2A05u, NULL}}                           },
    { 0x000Eu, 0x2A05u /* Service Changed                     */, 0x01200000u /* ind   */, 0x000Fu, {{0x0004u, (void *)&cyBle_attValuesLen[5]}} },
    { 0x000Fu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr */, 0x000Fu, {{0x0002u, (void *)&cyBle_attValuesLen[6]}} },
    { 0x0010u, 0x2800u /* Primary service                     */, 0x08000001u /*       */, 0x0013u, {{0x0010u, (void *)&cyBle_attValuesLen[7]}} },
    { 0x0011u, 0x2803u /* Characteristic                      */, 0x00000001u /*       */, 0x0013u, {{0x0010u, (void *)&cyBle_attValuesLen[8]}} },
    { 0x0012u, 0x7363u /* Custom Characteristic               */, 0x09000000u /*       */, 0x0013u, {{0x0001u, (void *)&cyBle_attValuesLen[9]}} },
    { 0x0013u, 0xA645u /* Custom Descriptor                   */, 0x09000001u /*       */, 0x0013u, {{0x0001u, (void *)&cyBle_attValuesLen[10]}} },
    { 0x0014u, 0x2800u /* Primary service                     */, 0x00000001u /*       */, 0x0020u, {{0x1809u, NULL}}                           },
    { 0x0015u, 0x2803u /* Characteristic                      */, 0x00200001u /* ind   */, 0x0017u, {{0x2A1Cu, NULL}}                           },
    { 0x0016u, 0x2A1Cu /* Temperature Measurement             */, 0x01200000u /* ind   */, 0x0017u, {{0x0005u, (void *)&cyBle_attValuesLen[11]}} },
    { 0x0017u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr */, 0x0017u, {{0x0002u, (void *)&cyBle_attValuesLen[12]}} },
    { 0x0018u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x0019u, {{0x2A1Du, NULL}}                           },
    { 0x0019u, 0x2A1Du /* Temperature Type                    */, 0x01020001u /* rd    */, 0x0019u, {{0x0001u, (void *)&cyBle_attValuesLen[13]}} },
    { 0x001Au, 0x2803u /* Characteristic                      */, 0x00100001u /* ntf   */, 0x001Cu, {{0x2A1Eu, NULL}}                           },
    { 0x001Bu, 0x2A1Eu /* Intermediate Temperature            */, 0x01100000u /* ntf   */, 0x001Cu, {{0x0005u, (void *)&cyBle_attValuesLen[14]}} },
    { 0x001Cu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr */, 0x001Cu, {{0x0002u, (void *)&cyBle_attValuesLen[15]}} },
    { 0x001Du, 0x2803u /* Characteristic                      */, 0x00020001u /* rd    */, 0x0020u, {{0x2A21u, NULL}}                           },
    { 0x001Eu, 0x2A21u /* Measurement Interval                */, 0x01020001u /* rd    */, 0x0020u, {{0x0002u, (void *)&cyBle_attValuesLen[16]}} },
    { 0x001Fu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr */, 0x001Fu, {{0x0002u, (void *)&cyBle_attValuesLen[17]}} },
    { 0x0020u, 0x2906u /* Valid Range                         */, 0x01020001u /* rd    */, 0x0020u, {{0x0004u, (void *)&cyBle_attValuesLen[18]}} },
};


#endif /* (CYBLE_GATT_ROLE_SERVER) */

#if(CYBLE_GATT_ROLE_CLIENT)
    
CYBLE_CLIENT_STATE_T cyBle_clientState;
CYBLE_GATTC_T cyBle_gattc;
CYBLE_GATT_ATTR_HANDLE_RANGE_T cyBle_gattcDiscoveryRange;
    
#endif /* (CYBLE_GATT_ROLE_CLIENT) */


#if(CYBLE_GATT_ROLE_SERVER)

/****************************************************************************** 
* Function Name: CyBle_GattsReInitGattDb
***************************************************************************//**
* 
*  Reinitializes the GATT database.
* 
*  \return
*  CYBLE_API_RESULT_T: A function result states if it succeeded or failed with
*  error codes:

*  Errors codes                          | Description
*  ------------                          | -----------
*  CYBLE_ERROR_OK						 | GATT database was reinitialized successfully.
*  CYBLE_ERROR_INVALID_STATE             | If the function is called in any state except CYBLE_STATE_DISCONNECTED.
*  CYBLE_ERROR_INVALID_PARAMETER         | If the Database has zero entries or is a NULL pointer.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattsReInitGattDb(void)
{
    CYBLE_API_RESULT_T apiResult;
    
    if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
    {
        apiResult = CyBle_GattsDbRegister(cyBle_gattDB, CYBLE_GATT_DB_INDEX_COUNT, CYBLE_GATT_DB_MAX_VALUE_LEN);
    }
    else
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    
    return(apiResult);
}


/****************************************************************************** 
* Function Name: CyBle_GattsWriteEventHandler
***************************************************************************//**
* 
*  Handles the Write Request Event for GATT service.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
*  \return
*  CYBLE_GATT_ERR_CODE_T: A function returns one of the following status 
*  values.

*  Errors codes                          | Description
*  --------------------                  | -----------
*  CYBLE_GATT_ERR_NONE                   | Write is successful.
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteEventHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam)
{
    CYBLE_GATT_ERR_CODE_T gattErr = CYBLE_GATT_ERR_NONE;
    
    /* Client Characteristic Configuration descriptor write request */
    if(eventParam->handleValPair.attrHandle == cyBle_gatts.cccdHandle)
    {
        /* Store value to database */
        gattErr = CyBle_GattsWriteAttributeValue(&eventParam->handleValPair, 0u, 
                        &eventParam->connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        
        if(gattErr == CYBLE_GATT_ERR_NONE)
        {
            if(CYBLE_IS_INDICATION_ENABLED_IN_PTR(eventParam->handleValPair.value.val))
            {
                CyBle_ApplCallback((uint32)CYBLE_EVT_GATTS_INDICATION_ENABLED, eventParam);
            }
            else
            {
                CyBle_ApplCallback((uint32)CYBLE_EVT_GATTS_INDICATION_DISABLED, eventParam);
            }
        }
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
    return (gattErr);
}


#endif /* (CYBLE_GATT_ROLE_SERVER) */

#if(CYBLE_GATT_ROLE_CLIENT)

/****************************************************************************** 
* Function Name: CyBle_GattcStartDiscovery
***************************************************************************//**
* 
*  Starts the automatic server discovery process. 
*   
*   Discovery procedure is based on the user configuration. It discovers only services, characteristics, 
*   descriptors which were declared in the GATT database.
*   Discovery procedure has the following flow:
*   - discovering primary services by BLE Stack function CyBle_GattcDiscoverAllPrimaryServices();
*   - discovering included services by BLE Stack function CyBle_GattcFindIncludedServices();
*   - discovering characteristics for available services by BLE Stack function CyBle_GattcDiscoverAllCharacteristics();
*   - discovering characteristic descriptors by BLE Stack function CyBle_GattcDiscoverAllCharacteristicDescriptors();
*
*   During the discovery procedure the discovery-specific stack events are handled by the component 
*   and thus aren’t passed to the application callback: CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP,
*   CYBLE_EVT_GATTC_READ_BY_TYPE_RSP, CYBLE_EVT_GATTC_FIND_INFO_RSP, CYBLE_EVT_GATTC_ERROR_RSP.              
*   
*   After the discovery procedure all information about available services is stored in CYBLE_DISC_SRVC_INFO_T structures,
*   and discovered attributes handles are stored in service-specific client structures, such as CYBLE_BASC_T for 
*   Battery Service or CYBLE_HRSC_T for Heart Rate Service.
*
*  \param connHandle: The handle which consists of the device ID and ATT connection ID.
* 
*  \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*                        failed. Following are the possible error codes.
*
*   <table>	
*   <tr>
*	  <th>Errors codes</th>
*	  <th>Description</th>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_OK</td>
*	  <td>On successful operation</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*	  <td>'connHandle' value does not represent any existing entry.</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_OPERATION</td>
*	  <td>The operation is not permitted</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*	  <td>Memory allocation failed</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_INVALID_STATE</td>
*	  <td>If the function is called in any state except connected or discovered</td>
*	</tr>
*   </table>
*
*  \events
*   The following events may be generated after calling this function:
*   * CYBLE_EVT_GATTC_DISCOVERY_COMPLETE  - event is generated when the remote device was successfully discovered. 
*   * CYBLE_EVT_GATTC_ERROR_RSP  		- is generated if the device discovery has failed.
*   * CYBLE_EVT_GATTC_SRVC_DUPLICATION 	- is generated if duplicate service record was found during the server device
*        								  discovery.
*   * CYBLE_EVT_GATTC_CHAR_DUPLICATION 	- is generated if duplicate service's characteristic descriptor record was found
*        								  during the server device discovery.
*   * CYBLE_EVT_GATTC_DESCR_DUPLICATION - is generated if duplicate service's characteristic descriptor record was found
*        								  during the server device discovery.
*  
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcStartDiscovery(CYBLE_CONN_HANDLE_T connHandle)
{
    uint8 j;
    CYBLE_API_RESULT_T apiResult;
    
    if((CyBle_GetState() != CYBLE_STATE_CONNECTED) || 
       ((CyBle_GetClientState() != CYBLE_CLIENT_STATE_CONNECTED) && 
        (CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED))) 
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else
    {
        /* Clean old discovery information */
        for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
        {
            (void)memset(&cyBle_serverInfo[j].range, 0, sizeof(cyBle_serverInfo[0].range));
        }

        cyBle_connHandle = connHandle;
        cyBle_gattcDiscoveryRange.startHandle = CYBLE_GATT_ATTR_HANDLE_START_RANGE;
        cyBle_gattcDiscoveryRange.endHandle = CYBLE_GATT_ATTR_HANDLE_END_RANGE;
        
        CyBle_ServiceInit();
        
        apiResult = CyBle_GattcDiscoverAllPrimaryServices(connHandle);

        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_SRVC_DISCOVERING);
            cyBle_eventHandlerFlag |= CYBLE_AUTO_DISCOVERY;
        }
    }
    
    return (apiResult);
}


/****************************************************************************** 
* Function Name: CyBle_GattcStartPartialDiscovery
***************************************************************************//**
* 
*  Starts the automatic server discovery process as per the range provided
*  on a GATT Server to which it is connected. This function could be used for 
*  partial server discovery after indication received to the Service Changed
*  Characteristic Value. 
* 
*  \param connHandle: The handle which consists of the device ID and ATT connection ID.
*  \param startHandle: Start of affected attribute handle range.
*  \param endHandle: End of affected attribute handle range.
* 
*  \return
*	CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*                        failed. Following are the possible error codes.
*
*   <table>	
*   <tr>
*	  <th>Errors codes</th>
*	  <th>Description</th>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_OK</td>
*	  <td>On successful operation</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*	  <td>'connHandle' value does not represent any existing entry.</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_OPERATION</td>
*	  <td>The operation is not permitted</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*	  <td>Memory allocation failed</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_INVALID_STATE</td>
*	  <td>If the function is called in any state except connected or discovered</td>
*	</tr>
*   </table>
* 
*  \events
*  Two events may be generated after calling this function:
*  CYBLE_EVT_GATTC_DISCOVERY_COMPLETE or CYBLE_EVT_GATTC_ERROR_RSP.
*  The CYBLE_EVT_GATTC_DISCOVERY_COMPLETE event is 
*  generated when the remote device was successfully discovered. The
*  CYBLE_EVT_GATTC_ERROR_RSP is generated if the device discovery is failed.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcStartPartialDiscovery(CYBLE_CONN_HANDLE_T connHandle,
                        CYBLE_GATT_DB_ATTR_HANDLE_T startHandle, CYBLE_GATT_DB_ATTR_HANDLE_T endHandle)
{
    uint8 j;
    CYBLE_API_RESULT_T apiResult;
    
    if((CyBle_GetState() != CYBLE_STATE_CONNECTED) || 
       ((CyBle_GetClientState() != CYBLE_CLIENT_STATE_CONNECTED) && 
        (CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED))) 
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else
    {
        /* Clean old discovery information of affected attribute range */
        for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
        {
            if((cyBle_serverInfo[j].range.startHandle >= startHandle) &&
               (cyBle_serverInfo[j].range.startHandle <= endHandle))
            {
                (void)memset(&cyBle_serverInfo[j].range, 0, sizeof(cyBle_serverInfo[0].range));
            }
        }

        cyBle_connHandle = connHandle;
        cyBle_gattcDiscoveryRange.startHandle = startHandle;
        cyBle_gattcDiscoveryRange.endHandle = endHandle;

        CyBle_ServiceInit();

        apiResult = CyBle_GattcDiscoverPrimaryServices(connHandle, &cyBle_gattcDiscoveryRange);

        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_SRVC_DISCOVERING);
            cyBle_eventHandlerFlag |= CYBLE_AUTO_DISCOVERY;
        }
    }
    
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharacteristicsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a CYBLE_EVT_GATTC_READ_BY_TYPE_RSP
*  event. Based on the service UUID, an appropriate data structure is populated
*  using the data received as part of the callback.
* 
*  \param discCharInfo: The pointer to a characteristic information structure.
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo)
{
    if(discCharInfo->uuid.uuid16 == CYBLE_UUID_CHAR_SERVICE_CHANGED)
    {
        CyBle_CheckStoreCharHandle(cyBle_gattc.serviceChanged);
    }
}


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharDescriptorsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a "CYBLE_EVT_GATTC_FIND_INFO_RSP" event.
*  Based on the descriptor UUID, an appropriate data structure is populated 
*  using the data received as part of the callback.
* 
*  \param discDescrInfo: The pointer to a descriptor information structure.
*  \param discoveryService: The index of the service instance
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcDiscoverCharDescriptorsEventHandler(CYBLE_DISC_DESCR_INFO_T *discDescrInfo)
{
    if(discDescrInfo->uuid.uuid16 == CYBLE_UUID_CHAR_CLIENT_CONFIG)
    {
        CyBle_CheckStoreCharDescrHandle(cyBle_gattc.cccdHandle);
    }
}


/******************************************************************************
* Function Name: CyBle_GattcIndicationEventHandler
***************************************************************************//**
* 
*  Handles the Indication Event.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_GattcIndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam)
{
    if(cyBle_gattc.serviceChanged.valueHandle == eventParam->handleValPair.attrHandle)
    {
        CyBle_ApplCallback((uint32)CYBLE_EVT_GATTC_INDICATION, eventParam);
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
}


#endif /* (CYBLE_GATT_ROLE_CLIENT) */


/* [] END OF FILE */
