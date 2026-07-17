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

#define SGFX_COLOR_L8       (0x08)
#define SGFX_COLOR_AL44     (0x44)
#define SGFX_COLOR_AL88     (0x88)
#define SGFX_COLOR_RGB444   (0x444)
#define SGFX_COLOR_ARGB1555 (0x1555)
#define SGFX_COLOR_ARGB4444 (0x4444)
#define SGFX_COLOR_RGB565   (0x565)
#define SGFX_COLOR_RGB666   (0x666)
#define SGFX_COLOR_RGB888   (0x888)
#define SGFX_COLOR_ARGB8888 (0x8888)

#define SGFX_LCD_COLOR_MODE SGFX_COLOR_RGB565

#define SGFX_FB0_COLOR_MODE SGFX_COLOR_RGB565

#define SGFX_FB1_COLOR_MODE SGFX_COLOR_ARGB8888


#define SGFX_LOG_ENABLE          1
#define SGFX_LOG_COLOR_ENABLE    1


#if SGFX_LOG_ENABLE
    #define SGFX_LOG_DISPLAY_ENABLE  1

    #define SGFX_LOG_LCD_ENABLE      1

    #define SGFX_LOG_ST7735_ENABLE   1

    #define SGFX_LOG_ST7789_ENABLE   1

    #define SGFX_LOG_ST7796_ENABLE   1

    #define SGFX_LOG_SPI_ENABLE      1
#else 
    #define SGFX_LOG_DISPLAY_ENABLE  0

    #define SGFX_LOG_LCD_ENABLE      0

    #define SGFX_LOG_ST7735_ENABLE   0

    #define SGFX_LOG_ST7789_ENABLE   0

    #define SGFX_LOG_ST7796_ENABLE   0

    #define SGFX_LOG_SPI_ENABLE      0
#endif


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


