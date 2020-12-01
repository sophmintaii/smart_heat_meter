/*****************************************************************************
* File Name: CommonFunctions.h
*
* Description:
* This file provides the declarations of the common system functions.
*
*****************************************************************************/
#if !defined (_COMMON_FUNCTIONS_H)
#define _COMMON_FUNCTIONS_H

#include <project.h>

/*****************************************************************************
* CONSTANT Declarations
*****************************************************************************/
#define             WAKEUP_SOURCE_WDT               (1u << 0)
#define             MEASUREMENT_INTERVAL            (1u << 1)
#define             SLEEP_DISABLED                  (1u << 2)
#define             ENABLE_HIBERNATE                (1u << 3)
#define             IMO_FREQUENCY_3MHZ              (3u)
#define             IMO_FREQUENCY_12MHZ             (12u)
    
/*****************************************************************************
* Extern variables
*****************************************************************************/
extern uint32 SystemFlag;

/*****************************************************************************
* Function Declarations
*****************************************************************************/
extern void InitializeSystem (void);

#endif  /* #if !defined (_BLE_HRM_H) */

/* [] END OF FILE */
