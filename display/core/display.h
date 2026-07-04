/**
 * @file display.h
 *
 */
  
#ifndef _DISPLAY_H
#define _DISPLAY_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *    DECLARATIONS
 *********************/

typedef struct display_painter display_painter_t;
typedef struct display_backlight display_backlight_t;


typedef void (* fill_point_fn_t)    (const display_painter_t ** self, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint32_t color);
typedef void (* fill_rectangle_fn_t)(const display_painter_t ** self, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint16_t w, 
                                     uint16_t h, 
                                     uint32_t color);
typedef void (* flush_fn_t)         (const display_painter_t ** self, 
                                     uint16_t x1, 
                                     uint16_t y1, 
                                     uint16_t x2, 
                                     uint16_t y2, 
                                     const void * data);
typedef void (* enable_backlight_fn_t)       (const display_backlight_t ** self);
typedef void (* disable_backlight_fn_t)      (const display_backlight_t ** self);
typedef void (* set_backlight_brightness_fn_t)(const display_backlight_t ** self, uint8_t brightness);


struct display_painter
{
    fill_point_fn_t     fill_point;
    fill_rectangle_fn_t fill_rectangle;
    flush_fn_t          flush;
};


struct display_backlight
{
    enable_backlight_fn_t        enable_backlight;
    disable_backlight_fn_t       disable_backlight;
    set_backlight_brightness_fn_t set_backlight_brightness;
};


struct display_context
{
    uint32_t color;
};
    
struct display
{
    const struct display_painter ** painter;
    const struct display_backlight ** backlight;
    struct display_context context;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/





#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_H*/


/******************************* (END OF FILE) *********************************/


