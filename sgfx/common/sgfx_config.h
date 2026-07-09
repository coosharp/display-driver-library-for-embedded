/**
 * @file display_config.h
 *
 */
  
#ifndef _DISPLAY_CONFIG_H
#define _DISPLAY_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
/*********************
 *      DEFINES
 *********************/
#define SGFX_LOG_ENABLE          (1)
#define SGFX_LOG_COLOR_ENABLE    (1)

#define SGFX_LOG_DISPLAY_ENABLE  (1)

#define SGFX_LOG_ST7735_ENABLE

#define SGFX_LOG_ST7789_ENABLE

#define SGFX_LOG_ST7796_ENABLE

#if SGFX_LOG_ENABLE
    #define    SGFX_LOG_PRINTF    printf
#else
    #define    SGFX_LOG_PRINTF
#endif

/*********************
 *    DECLARATIONS
 *********************/

/**********************
*  GLOBAL PROTOTYPES
 **********************/

 

#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_CONFIG_H*/


/******************************* (END OF FILE) *********************************/


