/**
 * @file display_factory.h
 *
 */
  
#ifndef _DISPLAY_FACTORY_H
#define _DISPLAY_FACTORY_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
typedef enum
{
    DISPLAY_PANEL_ST7735 = 0,
    DISPLAY_PANEL_ST7789,
    DISPLAY_PANEL_ILI9341,

    DISPLAY_PANEL_SIMPLE,

    DISPLAY_PANEL_MAX,
} display_panel_type_t;
/**********************
*  GLOBAL PROTOTYPES
 **********************/

 

#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_FACTORY_H*/


/******************************* (END OF FILE) *********************************/





