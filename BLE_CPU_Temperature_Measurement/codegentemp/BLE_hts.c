/***************************************************************************//**
* \file CYBLE_hts.c
* \version 3.30
* 
* \brief
*  Contains the source code for Health Thermometer Service.
* 
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "BLE_eventHandler.h"

static CYBLE_CALLBACK_T CyBle_HtsApplCallback = NULL;

#ifdef CYBLE_HTS_SERVER

const CYBLE_HTSS_T cyBle_htss =
{
    0x000Cu,    /* Handle of the HTS service */
    {
        
        /* Temperature Measurement characteristic */
        {
            0x000Eu, /* Handle of the Temperature Measurement characteristic */ 
            
            /* Array of Descriptors handles */
            {
                0x000Fu, /* Handle of the Client Characteristic Configuration descriptor */ 
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, 
            }, 
        }, 
        
        /* Temperature Type characteristic */
        {
            0x0011u, /* Handle of the Temperature Type characteristic */ 
            
            /* Array of Descriptors handles */
            {
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, 
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, 
            }, 
        }, 
        
        /* Intermediate Temperature characteristic */
        {
            CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, /* Handle of the Intermediate Temperature characteristic */ 
            
            /* Array of Descriptors handles */
            {
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, /* Handle of the Client Characteristic Configuration descriptor */ 
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, 
            }, 
        }, 
        
        /* Measurement Interval characteristic */
        {
            0x0013u, /* Handle of the Measurement Interval characteristic */ 
            
            /* Array of Descriptors handles */
            {
                CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE, /* Handle of the Client Characteristic Configuration descriptor */ 
                0x0014u, /* Handle of the Valid Range descriptor */ 
            }, 
        }, 
    },
};
static CYBLE_GATT_DB_ATTR_HANDLE_T cyBle_htssReqHandle;
    
#endif /* CYBLE_HTS_SERVER */

#ifdef CYBLE_HTS_CLIENT

CYBLE_HTSC_T cyBle_htsc;
static CYBLE_GATT_DB_ATTR_HANDLE_T cyBle_htscReqHandle;

#endif /* (CYBLE_HTS_CLIENT) */


/****************************************************************************** 
* Function Name: CyBle_HtsInit
***************************************************************************//**
* 
*  This function initializes HTS Service.
* 
******************************************************************************/
void CyBle_HtsInit(void)
{

#ifdef CYBLE_HTS_SERVER

    cyBle_htssReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
    
#endif /* CYBLE_HTS_SERVER */

#ifdef CYBLE_HTS_CLIENT

    if(cyBle_serverInfo[CYBLE_SRVI_HTS].range.startHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
    {
        (void)memset(&cyBle_htsc, 0, sizeof(cyBle_htsc));
    }
    cyBle_htscReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;

#endif /* CYBLE_HTS_CLIENT */
}


/******************************************************************************
* Function Name: CyBle_HtsRegisterAttrCallback
***************************************************************************//**
* 
*  Registers a callback function for service specific attribute operations.
*  Service specific write requests from peer device will not be handled with
*  unregistered callback function.
* 
*  \param callbackFunc: An application layer event callback function to receive 
*                     events from the BLE Component. The definition of 
*                     CYBLE_CALLBACK_T for HTS Service is:\n
*                     typedef void (* CYBLE_CALLBACK_T) (uint32 eventCode, 
*                                                        void *eventParam)
*                     * eventCode indicates the event that triggered this 
*                       callback (e.g. CYBLE_EVT_HTSS_NOTIFICATION_ENABLED).
*                     * eventParam contains the parameters corresponding to the 
*                       current event. (e.g. pointer to CYBLE_HTS_CHAR_VALUE_T
*                       structure that contains details of the characteristic 
*                       for which notification enabled event was triggered).
* 
******************************************************************************/
void CyBle_HtsRegisterAttrCallback(CYBLE_CALLBACK_T callbackFunc)
{
    CyBle_HtsApplCallback = callbackFunc;
}

#ifdef CYBLE_HTS_SERVER


/******************************************************************************
* Function Name: CyBle_HtssSetCharacteristicValue
***************************************************************************//**
* 
*  Sets the characteristic value of the service in the local database.
* 
*  \param charIndex: The index of the service characteristic.
*  \param attrSize: The size (in Bytes) of the characteristic value attribute.
*  \param attrValue: The pointer to the characteristic value data that should be
*               stored in the GATT database.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The request handled successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameter failed
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtssSetCharacteristicValue(CYBLE_HTS_CHAR_INDEX_T charIndex,
    uint8 attrSize, uint8 *attrValue)
{
    CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    CYBLE_GATT_HANDLE_VALUE_PAIR_T locHandleValuePair;

    if(charIndex >= CYBLE_HTS_CHAR_COUNT)
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        /* Store data in database */
        locHandleValuePair.attrHandle = cyBle_htss.charInfo[charIndex].charHandle;
        locHandleValuePair.value.len = attrSize;
        locHandleValuePair.value.val = attrValue;
        if(CYBLE_GATT_ERR_NONE !=
            CyBle_GattsWriteAttributeValue(&locHandleValuePair, 0u, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED))
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
    }
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtssGetCharacteristicValue
***************************************************************************//**
* 
*  Gets the characteristic value of the service, which is a value identified by
*  charIndex.
* 
*  \param charIndex: The index of the service characteristic.
*  \param attrSize: The size of the characteristic value attribute.
*  \param attrValue: The pointer to the location where characteristic value data
*               should be stored.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The request handled successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameter failed
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtssGetCharacteristicValue(CYBLE_HTS_CHAR_INDEX_T charIndex,
    uint8 attrSize, uint8 *attrValue)
{
    CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    CYBLE_GATT_HANDLE_VALUE_PAIR_T locHandleValuePair;

    if(charIndex >= CYBLE_HTS_CHAR_COUNT)
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        /* Read characteristic value from database */
        locHandleValuePair.attrHandle = cyBle_htss.charInfo[charIndex].charHandle;
        locHandleValuePair.value.len = attrSize;
        locHandleValuePair.value.val = attrValue;
        if(CYBLE_GATT_ERR_NONE !=
            CyBle_GattsReadAttributeValue(&locHandleValuePair, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED))
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
    }
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtssSetCharacteristicDescriptor
***************************************************************************//**
* 
*  Sets the characteristic descriptor of the specified characteristic.
* 
*  \param charIndex:  The index of the service characteristic.
*  \param descrIndex: The index of the service characteristic descriptor.
*  \param attrSize:   The size of the characteristic descriptor attribute.
*  \param attrValue: The pointer to the descriptor value data that should 
*              be stored in the GATT database. 
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The request handled successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameter failed
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtssSetCharacteristicDescriptor(CYBLE_HTS_CHAR_INDEX_T charIndex,
    CYBLE_HTS_DESCR_INDEX_T descrIndex, uint8 attrSize, uint8 *attrValue)
{
    CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    CYBLE_GATT_HANDLE_VALUE_PAIR_T locHandleValuePair;

    if((charIndex >= CYBLE_HTS_CHAR_COUNT) || (descrIndex >= CYBLE_HTS_DESCR_COUNT))
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        locHandleValuePair.attrHandle = cyBle_htss.charInfo[charIndex].descrHandle[descrIndex];
        if(locHandleValuePair.attrHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            locHandleValuePair.value.len = attrSize;
            locHandleValuePair.value.val = attrValue;
            if(CYBLE_GATT_ERR_NONE !=
                CyBle_GattsWriteAttributeValue(&locHandleValuePair, 0u, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED))
            {
                apiResult = CYBLE_ERROR_INVALID_PARAMETER;
            }
        }
        else
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
    }
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtssGetCharacteristicDescriptor
***************************************************************************//**
* 
*  Gets the characteristic descriptor of the specified characteristic.
* 
*  \param charIndex: The index of the service characteristic.
*  \param descrIndex: The index of the service characteristic descriptor.
*  \param attrSize: The size of the characteristic descriptor attribute.
*  \param attrValue: The pointer to the location where characteristic descriptor
*               value data should be stored.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The request handled successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameter failed
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtssGetCharacteristicDescriptor(CYBLE_HTS_CHAR_INDEX_T charIndex,
    CYBLE_HTS_DESCR_INDEX_T descrIndex, uint8 attrSize, uint8 *attrValue)
{
    CYBLE_API_RESULT_T apiResult = CYBLE_ERROR_OK;
    CYBLE_GATT_HANDLE_VALUE_PAIR_T locHandleValuePair;

    if((charIndex >= CYBLE_HTS_CHAR_COUNT) || (descrIndex >= CYBLE_HTS_DESCR_COUNT))
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        locHandleValuePair.attrHandle = cyBle_htss.charInfo[charIndex].descrHandle[descrIndex];
        if(locHandleValuePair.attrHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            locHandleValuePair.value.len = attrSize;
            locHandleValuePair.value.val = attrValue;
            if(CYBLE_GATT_ERR_NONE !=
                CyBle_GattsReadAttributeValue(&locHandleValuePair, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED))
            {
                apiResult = CYBLE_ERROR_INVALID_PARAMETER;
            }
        }
        else
        {
            apiResult = CYBLE_ERROR_INVALID_PARAMETER;
        }
    }
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtssWriteEventHandler
***************************************************************************//**
* 
*  Handles Write Request Event for HTS service.
* 
*  \param void *eventParam: The pointer to the data structure specified by the event.
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_HtssWriteEventHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam)
{
    CYBLE_HTS_CHAR_INDEX_T locCharIndex;
    CYBLE_HTS_CHAR_VALUE_T locCharValue;
    CYBLE_GATT_ERR_CODE_T gattErr = CYBLE_GATT_ERR_NONE;
    uint8 locReqHandle = 0u;

    if(NULL != CyBle_HtsApplCallback)
    {
        for(locCharIndex = CYBLE_HTS_TEMP_MEASURE; (locCharIndex < CYBLE_HTS_CHAR_COUNT) && (locReqHandle == 0u); 
            locCharIndex++)
        {
            
            if((eventParam->handleValPair.attrHandle == cyBle_htss.charInfo[locCharIndex].descrHandle[CYBLE_HTS_CCCD]) ||
               (eventParam->handleValPair.attrHandle == cyBle_htss.charInfo[locCharIndex].charHandle))
            {
                locCharValue.connHandle = eventParam->connHandle;
                locCharValue.charIndex = locCharIndex;
                locCharValue.value = &eventParam->handleValPair.value;
                /* Characteristic value write request */
                if(eventParam->handleValPair.attrHandle == cyBle_htss.charInfo[locCharIndex].charHandle)
                {
                    /* Validate Measure Interval value */
                    if(locCharIndex == CYBLE_HTS_MEASURE_INTERVAL)
                    {
                        uint8 locAttrValue[CYBLE_HTS_VRD_LEN];
                        uint16 requestValue;
                        
                        requestValue = CyBle_Get16ByPtr(eventParam->handleValPair.value.val);
                        
                        if(requestValue != 0u) /* 0 is valid interval value for no periodic measurement */
                        {
                            /* Check Valid range for Measure Interval characteristic value */
                            if(CyBle_HtssGetCharacteristicDescriptor(locCharIndex, CYBLE_HTS_VRD, 
                                                    CYBLE_HTS_VRD_LEN, locAttrValue) == CYBLE_ERROR_OK)
                            {
                                uint16 lowerValue;
                                uint16 upperValue;
                                
                                lowerValue = CyBle_Get16ByPtr(locAttrValue);
                                upperValue = CyBle_Get16ByPtr(locAttrValue + sizeof(lowerValue));
                                requestValue = CyBle_Get16ByPtr(eventParam->handleValPair.value.val);
                                if((requestValue != 0u) && ((requestValue < lowerValue) || (requestValue > upperValue)))
                                {
                                    gattErr = CYBLE_GATT_ERR_HTS_OUT_OF_RANGE;
                                }
                            }
                        }
                    }
                    if(gattErr == CYBLE_GATT_ERR_NONE)
                    {   /* Store value to database */
                        gattErr = CyBle_GattsWriteAttributeValue(&eventParam->handleValPair, 0u, 
                                    &eventParam->connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                        if(gattErr == CYBLE_GATT_ERR_NONE)
                        {
                            CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSS_CHAR_WRITE, &locCharValue);
                        }
                    }    
                }
                else /* Client Characteristic Configuration descriptor write request */
                {
                    /* Store value to database */
                    gattErr = CyBle_GattsWriteAttributeValue(&eventParam->handleValPair, 0u, 
                                    &eventParam->connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                    if(gattErr == CYBLE_GATT_ERR_NONE)
                    {
                        /* Check characteristic properties for Notification */
                        if(CYBLE_IS_NOTIFICATION_SUPPORTED(cyBle_htss.charInfo[locCharIndex].charHandle))
                        {
                            if(CYBLE_IS_NOTIFICATION_ENABLED_IN_PTR(eventParam->handleValPair.value.val))
                            {
                                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSS_NOTIFICATION_ENABLED, &locCharValue);
                            }
                            else
                            {
                                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSS_NOTIFICATION_DISABLED, &locCharValue);
                            }
                        }
                        /* Check characteristic properties for Indication */
                        if(CYBLE_IS_INDICATION_SUPPORTED(cyBle_htss.charInfo[locCharIndex].charHandle))
                        {
                            if(CYBLE_IS_INDICATION_ENABLED_IN_PTR(eventParam->handleValPair.value.val))
                            {
                                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSS_INDICATION_ENABLED, &locCharValue);
                            }
                            else
                            {
                                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSS_INDICATION_DISABLED, &locCharValue);
                            }
                        }
                    #if((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && \
                        (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
                        /* Set flag to store bonding data to flash */
                        if(cyBle_peerBonding == CYBLE_GAP_BONDING)
                        {
                            cyBle_pendingFlashWrite |= CYBLE_PENDING_CCCD_FLASH_WRITE_BIT;
                        }
                    #endif /* (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */
                        
                    }
                }
                cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
                locReqHandle = 1u;
            }
        }
    }
    return (gattErr);
}


/******************************************************************************
* Function Name: CyBle_HtssSendNotification
***************************************************************************//**
* 
*  Sends notification with a characteristic value of the Health Thermometer 
*  Service, which is a value specified by charIndex, to the Client device.
* 
*  On enabling notification successfully for a service characteristic, if the GATT
*  server has an updated value to be notified to the GATT Client, it sends out a
*  'Handle Value Notification' which results in CYBLE_EVT_HTSC_NOTIFICATION event
*  at the GATT Client's end.
*
*  \param connHandle: The connection handle.
*  \param charIndex: The index of the service characteristic.
*  \param attrSize: The size of the characteristic value attribute.
*  \param attrValue: The pointer to the characteristic value data that should be 
*               sent to the client's device.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*   * CYBLE_ERROR_OK - The request handled successfully
*   * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameter failed
*   * CYBLE_ERROR_INVALID_OPERATION - This operation is not permitted
*   * CYBLE_ERROR_INVALID_STATE - Connection with the client is not established
*   * CYBLE_ERROR_MEMORY_ALLOCATION_FAILED - Memory allocation failed. 
*   * CYBLE_ERROR_NTF_DISABLED - Notification is not enabled by the client.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtssSendNotification(CYBLE_CONN_HANDLE_T connHandle,
    CYBLE_HTS_CHAR_INDEX_T charIndex, uint8 attrSize, uint8 *attrValue)
{

    CYBLE_API_RESULT_T apiResult;
    
    /* Send Notification if it is enabled and connected */
    if(CYBLE_STATE_CONNECTED != CyBle_GetState())
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else if(!CYBLE_IS_NOTIFICATION_ENABLED(cyBle_htss.charInfo[charIndex].descrHandle[CYBLE_HTS_CCCD]))
    {
        apiResult = CYBLE_ERROR_NTF_DISABLED;
    }
    else
    {
        CYBLE_GATTS_HANDLE_VALUE_NTF_T ntfReqParam;
        
        /* Fill all fields of write request structure ... */
        ntfReqParam.attrHandle = cyBle_htss.charInfo[charIndex].charHandle;
        ntfReqParam.value.val = attrValue;
        ntfReqParam.value.len = attrSize;
        
        /* Send notification to client using previously filled structure */
        apiResult = CyBle_GattsNotification(connHandle, &ntfReqParam);
    }

    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtssSendIndication
***************************************************************************//**
* 
*  Sends indication with a characteristic value of the Health Thermometer 
*  Service, which is a value specified by charIndex, to the Client device.
*
*  On enabling indication successfully, if the GATT server has an updated value to be 
*  indicated to the GATT Client, it sends out a 'Handle Value Indication' which
*  results in CYBLE_EVT_HTSC_INDICATION or CYBLE_EVT_GATTC_HANDLE_VALUE_IND (if 
*  service specific callback function is not registered) event at the GATT Client's end.
*
*  \param connHandle: The connection handle.
*  \param charIndex:  The index of the service characteristic.
*  \param attrSize: The size of the characteristic value attribute.
*  \param attrValue: The pointer to the characteristic value data that should be
*               sent to the Client device.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*   * CYBLE_ERROR_OK - The request handled successfully
*   * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameter failed
*   * CYBLE_ERROR_INVALID_OPERATION - This operation is not permitted
*   * CYBLE_ERROR_INVALID_STATE - Connection with the client is not established
*   * CYBLE_ERROR_MEMORY_ALLOCATION_FAILED - Memory allocation failed
*   * CYBLE_ERROR_IND_DISABLED - Indication is not enabled by the client
*
* \events
*  In case of successful execution (return value = CYBLE_ERROR_OK)
*  the next events can appear: \n
*   If the HTS service-specific callback is registered 
*      (with CyBle_HtsRegisterAttrCallback):
*  * CYBLE_EVT_HTSS_INDICATION_CONFIRMED - in case if the indication is
*                                successfully delivered to the peer device.
*  .
*   Otherwise (if the HTS service-specific callback is not registered):
*  * CYBLE_EVT_GATTS_HANDLE_VALUE_CNF - in case if the indication is
*                                successfully delivered to the peer device.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtssSendIndication(CYBLE_CONN_HANDLE_T connHandle,
    CYBLE_HTS_CHAR_INDEX_T charIndex, uint8 attrSize, uint8 *attrValue)
{
    CYBLE_API_RESULT_T apiResult;
    
    /* Send Notification if it is enabled and connected */
    if(CYBLE_STATE_CONNECTED != CyBle_GetState())
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else if(!CYBLE_IS_INDICATION_ENABLED(cyBle_htss.charInfo[charIndex].descrHandle[CYBLE_HTS_CCCD]))
    {
        apiResult = CYBLE_ERROR_IND_DISABLED;
    }
    else
    {
        CYBLE_GATTS_HANDLE_VALUE_NTF_T ntfReqParam;
        
        /* Fill all fields of write request structure ... */
        ntfReqParam.attrHandle = cyBle_htss.charInfo[charIndex].charHandle;
        ntfReqParam.value.val = attrValue;
        ntfReqParam.value.len = attrSize;
        
        /* Send indication to client using previously filled structure */
        apiResult = CyBle_GattsIndication(connHandle, &ntfReqParam);
        /* Save handle to support service specific value confirmation response from client */
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_htssReqHandle = ntfReqParam.attrHandle;
        }
    }
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtssConfirmationEventHandler
***************************************************************************//**
* 
*  Handles a Value Confirmation request event from the BLE stack.
* 
*  *eventParam - The pointer to a structure of type CYBLE_CONN_HANDLE_T.
* 
******************************************************************************/
void CyBle_HtssConfirmationEventHandler(const CYBLE_CONN_HANDLE_T *eventParam)
{
    CYBLE_HTS_CHAR_INDEX_T locCharIndex;
    CYBLE_HTS_CHAR_VALUE_T locCharValue;
    uint8 locReqHandle = 0u;

    if((NULL != CyBle_HtsApplCallback) && (CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE != cyBle_htssReqHandle))
    {
        for(locCharIndex = CYBLE_HTS_TEMP_MEASURE; (locCharIndex < CYBLE_HTS_CHAR_COUNT) && (locReqHandle == 0u); 
            locCharIndex++)
        {
            if(cyBle_htssReqHandle == cyBle_htss.charInfo[locCharIndex].charHandle)
            {
                locCharValue.connHandle = *eventParam;
                locCharValue.charIndex = locCharIndex;
                locCharValue.value = NULL;
                cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
                cyBle_htssReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSS_INDICATION_CONFIRMED, &locCharValue);
                locReqHandle = 1u;
            }
        }
    }
}


#endif /* CYBLE_HTS_SERVER */

#ifdef CYBLE_HTS_CLIENT


/******************************************************************************
* Function Name: CyBle_HtscDiscoverCharacteristicsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a CYBLE_EVT_GATTC_READ_BY_TYPE_RSP
*  event. Based on the service UUID, an appropriate data structure is populated
*  using the data received as part of the callback.
* 
*  \param discCharInfo: The pointer to a characteristic information structure.
* 
******************************************************************************/
void CyBle_HtscDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo)
{
    /* HTS characteristics UUIDs */
    static const CYBLE_UUID16 cyBle_htscCharUuid[CYBLE_HTS_CHAR_COUNT] =
    {
        CYBLE_UUID_CHAR_TEMPERATURE_MSMNT,
        CYBLE_UUID_CHAR_TEMPERATURE_TYPE,
        CYBLE_UUID_CHAR_INTERMEDIATE_TEMP,
        CYBLE_UUID_CHAR_MSMNT_INTERVAL    
    };
    uint8 i;
    static CYBLE_GATT_DB_ATTR_HANDLE_T *htsLastEndHandle = NULL;

    /* Update last characteristic endHandle to declaration handle of this characteristic */ 
    if(htsLastEndHandle != NULL)
    {
        *htsLastEndHandle = discCharInfo->charDeclHandle - 1u;
        htsLastEndHandle = NULL;
    }

    for(i = (uint8) CYBLE_HTS_TEMP_MEASURE; i < (uint8) CYBLE_HTS_CHAR_COUNT; i++)
    {
        if(cyBle_htscCharUuid[i] == discCharInfo->uuid.uuid16)
        {
            CyBle_CheckStoreCharHandle(cyBle_htsc.charInfo[i]);
            htsLastEndHandle = &cyBle_htsc.charInfo[i].endHandle;
            break;
        }
    }
    
    /* Init characteristic endHandle to the Service endHandle.
       Characteristic endHandle will be updated to declaration
       handler of the following characteristic,
       in the following characteristic discovery procedure. */
    if(htsLastEndHandle != NULL)
    {
        *htsLastEndHandle = cyBle_serverInfo[cyBle_disCount].range.endHandle;
    }    
    
}


/******************************************************************************
* Function Name: CyBle_HtscDiscoverCharDescriptorsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a CYBLE_EVT_GATTC_FIND_INFO_RSP event.
*  Based on the descriptor UUID, an appropriate data structure is populated using
*  the data received as part of the callback.
* 
*  \param discoveryCharIndex: The characteristic index which is discovered.
*  \param discDescrInfo: The pointer to a descriptor information structure.
* 
******************************************************************************/
void CyBle_HtscDiscoverCharDescriptorsEventHandler(CYBLE_HTS_CHAR_INDEX_T discoveryCharIndex, 
                                                   CYBLE_DISC_DESCR_INFO_T *discDescrInfo)
{
    CYBLE_HTS_DESCR_INDEX_T locDescIndex;

    if(discDescrInfo->uuid.uuid16 == CYBLE_UUID_CHAR_CLIENT_CONFIG)
    {
        locDescIndex = CYBLE_HTS_CCCD;
    }
    else if(discDescrInfo->uuid.uuid16 == CYBLE_UUID_CHAR_VALID_RANGE)
    {
        locDescIndex = CYBLE_HTS_VRD;
    }
    else    /* Not supported descriptor */
    {
        locDescIndex = CYBLE_HTS_DESCR_COUNT;
    }

    if(locDescIndex < CYBLE_HTS_DESCR_COUNT)
    {
        if(cyBle_htsc.charInfo[discoveryCharIndex].descrHandle[locDescIndex] == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
        {
            cyBle_htsc.charInfo[discoveryCharIndex].descrHandle[locDescIndex] = discDescrInfo->descrHandle;
        }
        else    /* Duplication of descriptor */
        {
            CyBle_ApplCallback(CYBLE_EVT_GATTC_DESCR_DUPLICATION, &discDescrInfo->uuid);
        }
    }
}


/******************************************************************************
* Function Name: CyBle_HtscSetCharacteristicValue
***************************************************************************//**
* 
*  This function is used to write the characteristic (which is identified by
*  charIndex) value attribute in the server. As a result a Write Request is 
*  sent to the GATT Server and on successful execution of the request on the 
*  Server side the CYBLE_EVT_HTSS_CHAR_WRITE events is generated.
*  On successful request execution on the Server side the Write Response is 
*  sent to the Client.
* 
*  \param connHandle: The connection handle.
*  \param charIndex: The index of the service characteristic.
*  \param attrSize: The size of the characteristic value attribute.
*  \param attrValue: The pointer to the characteristic value data that should be 
*               sent to the server device.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The request was sent successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameters failed
*  * CYBLE_ERROR_MEMORY_ALLOCATION_FAILED - Memory allocation failed
*  * CYBLE_ERROR_INVALID_STATE - Connection with the server is not established
*  * CYBLE_ERROR_GATT_DB_INVALID_ATTR_HANDLE - The peer device doesn't have
*                                               the particular characteristic
*  * CYBLE_ERROR_INVALID_OPERATION - Operation is invalid for this
*                                     characteristic
*
* \events
*  In case of successful execution (return value = CYBLE_ERROR_OK)
*  the next events can appear: \n
*   If the HTS service-specific callback is registered 
*      (with CyBle_HtsRegisterAttrCallback):
*  * CYBLE_EVT_HTSC_WRITE_CHAR_RESPONSE - in case if the requested attribute is
*                                successfully wrote on the peer device,
*                                the details (char index, etc.) are 
*                                provided with event parameter structure
*                                of type CYBLE_HTS_CHAR_VALUE_T.
*  .
*   Otherwise (if the HTS service-specific callback is not registered):
*  * CYBLE_EVT_GATTC_WRITE_RSP - in case if the requested attribute is 
*                                successfully wrote on the peer device.
*  * CYBLE_EVT_GATTC_ERROR_RSP - in case if there some trouble with the 
*                                requested attribute on the peer device,
*                                the details are provided with event parameters 
*                                structure (CYBLE_GATTC_ERR_RSP_PARAM_T).
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtscSetCharacteristicValue(CYBLE_CONN_HANDLE_T connHandle, CYBLE_HTS_CHAR_INDEX_T charIndex,
    uint8 attrSize, uint8 * attrValue)
{
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GATT_HANDLE_VALUE_PAIR_T writeReqParam;

    if(CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED)
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else if(charIndex >= CYBLE_HTS_CHAR_COUNT)
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else if(cyBle_htsc.charInfo[charIndex].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
    {
        writeReqParam.attrHandle = cyBle_htsc.charInfo[charIndex].valueHandle;
        writeReqParam.value.val = attrValue;
        writeReqParam.value.len = attrSize;

        apiResult = CyBle_GattcWriteCharacteristicValue(connHandle, &writeReqParam);
        /* Save handle to support service specific write response from device */
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_htscReqHandle = writeReqParam.attrHandle;
        }
    }
    else
    {
        apiResult = CYBLE_ERROR_GATT_DB_INVALID_ATTR_HANDLE;
    }
    
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtscGetCharacteristicValue
***************************************************************************//**
* 
*  This function is used to read a characteristic value, which is a value 
*  identified by charIndex, from the server.
* 
*  \param connHandle: The connection handle.
*  \param charIndex: The index of the service characteristic.
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The read request was sent successfully  
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameters failed
*  * CYBLE_ERROR_GATT_DB_INVALID_ATTR_HANDLE - The peer device doesn't have
*                                               the particular characteristic
*  * CYBLE_ERROR_MEMORY_ALLOCATION_FAILED - Memory allocation failed
*  * CYBLE_ERROR_INVALID_STATE - Connection with the server is not established
*  * CYBLE_ERROR_INVALID_OPERATION - Operation is invalid for this 
*                                     characteristic
*
* \events
*  In case of successful execution (return value = CYBLE_ERROR_OK)
*  the next events can appear: \n
*   If the HTS service-specific callback is registered 
*      (with CyBle_HtsRegisterAttrCallback):
*  * CYBLE_EVT_HTSC_READ_CHAR_RESPONSE - in case if the requested attribute is
*                                successfully wrote on the peer device,
*                                the details (char index , value, etc.) are 
*                                provided with event parameter structure
*                                of type CYBLE_HTS_CHAR_VALUE_T.
*  .
*   Otherwise (if the HTS service-specific callback is not registered):
*  * CYBLE_EVT_GATTC_READ_RSP - in case if the requested attribute is 
*                                successfully read on the peer device,
*                                the details (handle, value, etc.) are 
*                                provided with event parameters 
*                                structure (CYBLE_GATTC_READ_RSP_PARAM_T).
*  * CYBLE_EVT_GATTC_ERROR_RSP - in case if there some trouble with the 
*                                requested attribute on the peer device,
*                                the details are provided with event parameters 
*                                structure (CYBLE_GATTC_ERR_RSP_PARAM_T).
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtscGetCharacteristicValue(CYBLE_CONN_HANDLE_T connHandle, CYBLE_HTS_CHAR_INDEX_T charIndex)
{
    CYBLE_API_RESULT_T apiResult;

    if(CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED)
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else if(charIndex >= CYBLE_HTS_CHAR_COUNT)
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else if(cyBle_htsc.charInfo[charIndex].valueHandle != CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)
    {
        apiResult = CyBle_GattcReadCharacteristicValue(connHandle, 
                                                       cyBle_htsc.charInfo[charIndex].valueHandle);
        /* Save handle to support service specific read response from device */
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_htscReqHandle = cyBle_htsc.charInfo[charIndex].valueHandle;
        }
    }
    else
    {
        apiResult = CYBLE_ERROR_GATT_DB_INVALID_ATTR_HANDLE;
    }
    
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtscSetCharacteristicDescriptor
***************************************************************************//**
* 
*  This function is used to write the characteristic descriptor to the server,
*  which is identified by charIndex and descrIndex.
* 
*  Internally, Write Request is sent to the GATT Server and on successful 
*  execution of the request on the Server side the following events can be 
*  generated: 
*  * CYBLE_EVT_HTSS_NOTIFICATION_ENABLED 
*  * CYBLE_EVT_HTSS_NOTIFICATION_ENABLED
*  * CYBLE_EVT_HTSS_INDICATION_ENABLED 
*  * CYBLE_EVT_HTSS_INDICATION_DISABLED
* 
*  \param connHandle: The connection handle.
*  \param charIndex: The index of the service characteristic.
*  \param descrIndex: The index of the service characteristic descriptor.
*  \param attrSize: The size of the characteristic value attribute.
*  \param attrValue: The pointer to the characteristic descriptor value data that 
*               should be sent to the server device. 
* 
* \return
*  Return value is of type CYBLE_API_RESULT_T.
*  * CYBLE_ERROR_OK - The request was sent successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameters failed
*  * CYBLE_ERROR_INVALID_STATE - The state is not valid
*  * CYBLE_ERROR_MEMORY_ALLOCATION_FAILED - Memory allocation failed
*  * CYBLE_ERROR_INVALID_OPERATION - This operation is not permitted on 
*                                     the specified attribute
*
* \events
*  In case of successful execution (return value = CYBLE_ERROR_OK)
*  the next events can appear: \n
*   If the HTS service-specific callback is registered 
*      (with CyBle_HtsRegisterAttrCallback):
*  * CYBLE_EVT_HTSC_WRITE_DESCR_RESPONSE - in case if the requested attribute is
*                                successfully wrote on the peer device,
*                                the details (char index, descr index etc.) are 
*                                provided with event parameter structure
*                                of type CYBLE_HTS_DESCR_VALUE_T.
*  .
*   Otherwise (if the HTS service-specific callback is not registered):
*  * CYBLE_EVT_GATTC_WRITE_RSP - in case if the requested attribute is 
*                                successfully wrote on the peer device.
*  * CYBLE_EVT_GATTC_ERROR_RSP - in case if there some trouble with the 
*                                requested attribute on the peer device,
*                                the details are provided with event parameters 
*                                structure (CYBLE_GATTC_ERR_RSP_PARAM_T).
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtscSetCharacteristicDescriptor(CYBLE_CONN_HANDLE_T connHandle,
    CYBLE_HTS_CHAR_INDEX_T charIndex, CYBLE_HTS_DESCR_INDEX_T descrIndex, uint8 attrSize, uint8 *attrValue)
{
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GATTC_WRITE_REQ_T writeReqParam;

    if(CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED)
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else if((charIndex >= CYBLE_HTS_CHAR_COUNT) || (descrIndex >= CYBLE_HTS_DESCR_COUNT))
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else if(descrIndex != CYBLE_HTS_CCCD)
    {
        apiResult = CYBLE_ERROR_INVALID_OPERATION;
    }
    else
    {
     /* Fill all fields of write request structure ... */
        writeReqParam.attrHandle = cyBle_htsc.charInfo[charIndex].descrHandle[CYBLE_HTS_CCCD];
        writeReqParam.value.val = attrValue;
        writeReqParam.value.len = attrSize;

        /* ... and send request to server device. */
        apiResult = CyBle_GattcWriteCharacteristicDescriptors(connHandle, &writeReqParam);
        
        /* Save handle to support service specific read response from device */
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_htscReqHandle = writeReqParam.attrHandle;
        }
    }
    
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtscGetCharacteristicDescriptor
***************************************************************************//**
* 
*  Gets the characteristic descriptor of the specified characteristic of the
*  service.
* 
*  \param connHandle: The connection handle.
*  \param charIndex: The index of the service characteristic.
*  \param descrIndex: The index of the service characteristic descriptor.
* 
* \return
*  * CYBLE_ERROR_OK - The request was sent successfully
*  * CYBLE_ERROR_INVALID_PARAMETER - Validation of the input parameters failed
*  * CYBLE_ERROR_INVALID_STATE - The state is not valid
*  * CYBLE_ERROR_MEMORY_ALLOCATION_FAILED - Memory allocation failed
*  * CYBLE_ERROR_INVALID_OPERATION - This operation is not permitted on 
*                                     the specified attribute
*
* \events
*  In case of successful execution (return value = CYBLE_ERROR_OK)
*  the next events can appear: \n
*  If the HTS service-specific callback is registered 
*      (with CyBle_HtsRegisterAttrCallback):
*  * CYBLE_EVT_HTSC_READ_DESCR_RESPONSE - in case if the requested attribute is
*                                successfully wrote on the peer device,
*                                the details (char index, descr index, value, etc.) 
*                                are provided with event parameter structure
*                                of type CYBLE_HTS_DESCR_VALUE_T. 
*  .
*  Otherwise (if the HTS service-specific callback is not registered):
*  * CYBLE_EVT_GATTC_READ_RSP - in case if the requested attribute is 
*                                successfully read on the peer device,
*                                the details (handle, value, etc.) are 
*                                provided with event parameters 
*                                structure (CYBLE_GATTC_READ_RSP_PARAM_T).
*  * CYBLE_EVT_GATTC_ERROR_RSP - in case if there some trouble with the 
*                                requested attribute on the peer device,
*                                the details are provided with event parameters 
*                                structure (CYBLE_GATTC_ERR_RSP_PARAM_T).
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_HtscGetCharacteristicDescriptor(CYBLE_CONN_HANDLE_T connHandle,
    CYBLE_HTS_CHAR_INDEX_T charIndex, CYBLE_HTS_DESCR_INDEX_T descrIndex)
{
    CYBLE_API_RESULT_T apiResult;
    
    if(CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED)
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else if((charIndex >= CYBLE_HTS_CHAR_COUNT) || (descrIndex >= CYBLE_HTS_DESCR_COUNT))
    {
        apiResult = CYBLE_ERROR_INVALID_PARAMETER;
    }
    else
    {
        apiResult = CyBle_GattcReadCharacteristicDescriptors(connHandle, 
                                                    cyBle_htsc.charInfo[charIndex].descrHandle[descrIndex]);
        
        /* Save handle to support service specific read response from device */
        if(apiResult == CYBLE_ERROR_OK)
        {
            cyBle_htscReqHandle = cyBle_htsc.charInfo[charIndex].descrHandle[descrIndex];
        }
    }

    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_HtscNotificationEventHandler
***************************************************************************//**
* 
*  Handles Notification Event.
* 
*  \param eventParam: The pointer to the data structure specified by an event.
* 
******************************************************************************/
void CyBle_HtscNotificationEventHandler(CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T *eventParam)
{
    CYBLE_HTS_CHAR_INDEX_T locCharIndex;
    CYBLE_HTS_CHAR_VALUE_T notifValue;

    if(NULL != CyBle_HtsApplCallback)
    {
        for(locCharIndex = CYBLE_HTS_TEMP_MEASURE; locCharIndex < CYBLE_HTS_CHAR_COUNT; locCharIndex++)
        {
            if(cyBle_htsc.charInfo[locCharIndex].valueHandle == eventParam->handleValPair.attrHandle)
            {
                notifValue.connHandle = eventParam->connHandle;
                notifValue.charIndex = locCharIndex;
                notifValue.value = &eventParam->handleValPair.value;
                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSC_NOTIFICATION, &notifValue);
                cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
                break;
            }
        }
    }
}


/******************************************************************************
* Function Name: CyBle_HtscIndicationEventHandler
***************************************************************************//**
* 
*  Handles Indication Event.
* 
*  \param eventParam: The pointer to the data structure specified by an event.
* 
******************************************************************************/
void CyBle_HtscIndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam)
{
    CYBLE_HTS_CHAR_INDEX_T locCharIndex;
    CYBLE_HTS_CHAR_VALUE_T indicationValue;

    if(NULL != CyBle_HtsApplCallback)
    {
        for(locCharIndex = CYBLE_HTS_TEMP_MEASURE; locCharIndex < CYBLE_HTS_CHAR_COUNT; locCharIndex++)
        {
            if(cyBle_htsc.charInfo[locCharIndex].valueHandle == eventParam->handleValPair.attrHandle)
            {
                indicationValue.connHandle = eventParam->connHandle;
                indicationValue.charIndex = locCharIndex;
                indicationValue.value = &eventParam->handleValPair.value;
                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSC_INDICATION, &indicationValue);
                cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
                break;
            }
        }
    }
}


/******************************************************************************
* Function Name: CyBle_HtscReadResponseEventHandler
***************************************************************************//**
* 
*  Handles Read Response Event.
* 
*  \param eventParam: The pointer to the data structure specified by an event.
* 
******************************************************************************/
void CyBle_HtscReadResponseEventHandler(CYBLE_GATTC_READ_RSP_PARAM_T *eventParam)
{
    uint8 locReqHandle = 0u;
    CYBLE_HTS_CHAR_INDEX_T locCharIndex;

    if((NULL != CyBle_HtsApplCallback) && (CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE != cyBle_htscReqHandle))
    {
        for(locCharIndex = CYBLE_HTS_TEMP_MEASURE; (locCharIndex < CYBLE_HTS_CHAR_COUNT) && (locReqHandle == 0u); 
            locCharIndex++)
        {
            if(cyBle_htscReqHandle == cyBle_htsc.charInfo[locCharIndex].valueHandle)
            {
                CYBLE_HTS_CHAR_VALUE_T locCharValue;
                
                locCharValue.connHandle = eventParam->connHandle;
                locCharValue.charIndex = locCharIndex;
                locCharValue.value = &eventParam->value;
                cyBle_htscReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSC_READ_CHAR_RESPONSE, &locCharValue);
                locReqHandle = 1u;
            }
            else
            {
                CYBLE_HTS_DESCR_INDEX_T locDescIndex;

                for(locDescIndex = CYBLE_HTS_CCCD; (locDescIndex < CYBLE_HTS_DESCR_COUNT) &&
                   (locReqHandle == 0u); locDescIndex++)
                {
                    if(cyBle_htscReqHandle == cyBle_htsc.charInfo[locCharIndex].descrHandle[locDescIndex])
                    {
                        CYBLE_HTS_DESCR_VALUE_T locDescrValue;
                        
                        locDescrValue.connHandle = eventParam->connHandle;
                        locDescrValue.charIndex = locCharIndex;
                        locDescrValue.descrIndex = locDescIndex;
                        locDescrValue.value = &eventParam->value;
                        cyBle_htscReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
                        CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSC_READ_DESCR_RESPONSE, &locDescrValue);
                        locReqHandle = 1u;
                    }
                }
            }
        }
        if(locReqHandle != 0u)
        {
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
        }
    }
}


/******************************************************************************
* Function Name: CyBle_HtscWriteResponseEventHandler
***************************************************************************//**
* 
*  Handles Write Response Event.
* 
*  \param eventParam: The pointer to a data structure specified by the event.
* 
******************************************************************************/
void CyBle_HtscWriteResponseEventHandler(const CYBLE_CONN_HANDLE_T *eventParam)
{
    uint8 locReqHandle = 0u;
    CYBLE_HTS_CHAR_INDEX_T locCharIndex;
    
    if((NULL != CyBle_HtsApplCallback) && (CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE != cyBle_htscReqHandle))
    {
        for(locCharIndex = CYBLE_HTS_TEMP_MEASURE; (locCharIndex < CYBLE_HTS_CHAR_COUNT) && (locReqHandle == 0u); 
            locCharIndex++)
        {
            if(cyBle_htscReqHandle == cyBle_htsc.charInfo[locCharIndex].valueHandle)
            {
                CYBLE_HTS_CHAR_VALUE_T locCharValue;
                
                locCharValue.connHandle = *eventParam;
                locCharValue.charIndex = locCharIndex;
                locCharValue.value = NULL;
                cyBle_htscReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSC_WRITE_CHAR_RESPONSE, &locCharValue);
                locReqHandle = 1u;
            }
            else if(cyBle_htscReqHandle == cyBle_htsc.charInfo[locCharIndex].descrHandle[CYBLE_HTS_CCCD])
            {
                CYBLE_HTS_DESCR_VALUE_T locDescrValue;
                
                locDescrValue.connHandle = *eventParam;
                locDescrValue.charIndex = locCharIndex;
                locDescrValue.descrIndex = CYBLE_HTS_CCCD;
                locDescrValue.value = NULL;
                cyBle_htscReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
                CyBle_HtsApplCallback((uint32)CYBLE_EVT_HTSC_WRITE_DESCR_RESPONSE, &locDescrValue);
                locReqHandle = 1u;
            }
            else /* No other destination for write operation is possible */
            {
            }
        }
        if(locReqHandle != 0u)
        {
            cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
        }
    }
}


/******************************************************************************
* Function Name: CyBle_HtscErrorResponseEventHandler
***************************************************************************//**
* 
*  Handles Error Response Event.
* 
*  \param eventParam: The pointer to a data structure specified by an event.
* 
******************************************************************************/
void CyBle_HtscErrorResponseEventHandler(const CYBLE_GATTC_ERR_RSP_PARAM_T *eventParam)
{
    if((eventParam != NULL) && (eventParam->attrHandle == cyBle_htscReqHandle))
    {
        cyBle_htscReqHandle = CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE;
    }
}

#endif /* (CYBLE_HTS_CLIENT) */


/* [] END OF FILE */

