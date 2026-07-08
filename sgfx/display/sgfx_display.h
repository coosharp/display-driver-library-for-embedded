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

typedef struct display_drawing display_drawing_t;
typedef struct display_backlight display_backlight_t;


typedef void (* fill_point_fn_t)    (const display_drawing_t ** self, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint32_t color);
typedef void (* fill_rectangle_fn_t)(const display_drawing_t ** self, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint16_t w, 
                                     uint16_t h, 
                                     uint32_t color);
typedef void (* flush_fn_t)         (const display_drawing_t ** self, 
                                     uint16_t x1, 
                                     uint16_t y1, 
                                     uint16_t x2, 
                                     uint16_t y2, 
                                     const void * data);
typedef int  (* ioctrl_fn_t)        (const display_drawing_t ** self, 
                                     uint32_t command, 
                                     void * arg);

typedef void (* set_backlight_state_fn_t)       (const display_backlight_t ** self, uint8_t state);
typedef void (* get_backlight_state_fn_t)      (const display_backlight_t ** self, uint8_t * state);
typedef void (* set_backlight_brightness_fn_t)(const display_backlight_t ** self, uint8_t brightness);
typedef void (* get_backlight_brightness_fn_t)(const display_backlight_t ** self, uint8_t * brightness);

struct display_drawing
{
    fill_point_fn_t     fill_point;
    fill_rectangle_fn_t fill_rectangle;
    flush_fn_t          flush;
    ioctrl_fn_t         ioctrl;
};


struct display_backlight
{
    set_backlight_state_fn_t       set_backlight_state;
    get_backlight_state_fn_t       get_backlight_state;
    set_backlight_brightness_fn_t set_backlight_brightness;
    get_backlight_brightness_fn_t get_backlight_brightness;
};


struct display_context
{
    uint32_t color;
};
    
struct display
{
    const struct display_drawing ** drawing;
    const struct display_backlight ** backlight;
    struct display_context context;
};


enum display_ioctrl_command
{
    DISPLAY_IOCTRL_NONE = 0,

    DISPLAY_IOCTRL_GET_WIDTH,
    DISPLAY_IOCTRL_GET_HEIGHT,
    DISPLAY_IOCTRL_GET_ROTATION,
};



/**********************
*  GLOBAL PROTOTYPES
 **********************/
void display_register_instance(struct display * self, 
                               const struct display_drawing ** drawing, 
                               const struct display_backlight ** backlight);




#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_H*/


/******************************* (END OF FILE) *********************************/


