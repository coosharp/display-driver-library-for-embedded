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

typedef struct sgfx_display_drawing sgfx_display_drawing_t;
typedef struct sgfx_display_backlight sgfx_display_backlight_t;


typedef void (* display_fill_point_fn_t)    (const sgfx_display_drawing_t ** drawing, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint32_t color);
typedef void (* display_fill_rectangle_fn_t)(const sgfx_display_drawing_t ** drawing, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint16_t w, 
                                     uint16_t h, 
                                     uint32_t color);
typedef void (* display_flush_fn_t)         (const sgfx_display_drawing_t ** drawing, 
                                     uint16_t x1, 
                                     uint16_t y1, 
                                     uint16_t x2, 
                                     uint16_t y2, 
                                     const void * data);
typedef int  (* display_ioctrl_fn_t)        (const sgfx_display_drawing_t ** drawing, 
                                     uint32_t command, 
                                     void * arg);

typedef void (* display_set_backlight_state_fn_t)       (const sgfx_display_backlight_t ** self, uint8_t state);
typedef void (* display_get_backlight_state_fn_t)      (const sgfx_display_backlight_t ** self, uint8_t * state);
typedef void (* display_set_backlight_brightness_fn_t)(const sgfx_display_backlight_t ** self, uint8_t brightness);
typedef void (* display_get_backlight_brightness_fn_t)(const sgfx_display_backlight_t ** self, uint8_t * brightness);

struct sgfx_display_drawing
{
    display_fill_point_fn_t     fill_point;
    display_fill_rectangle_fn_t fill_rectangle;
    display_flush_fn_t          flush;
    display_ioctrl_fn_t         ioctrl;
};


struct sgfx_display_backlight
{
    display_set_backlight_state_fn_t       set_backlight_state;
    display_get_backlight_state_fn_t       get_backlight_state;
    display_set_backlight_brightness_fn_t set_backlight_brightness;
    display_get_backlight_brightness_fn_t get_backlight_brightness;
};


struct sgfx_display_context
{
    uint32_t color;
};
    
struct sgfx_display
{
    const struct sgfx_display_drawing ** drawing;
    const struct sgfx_display_backlight ** backlight;
    struct sgfx_display_context context;
};


typedef enum 
{
    SGFX_DISPLAY_NONE = 0,

    SGFX_DISPLAY_GET_WIDTH,
    SGFX_DISPLAY_GET_HEIGHT,
    SGFX_DISPLAY_GET_ROTATION,
}sgfx_display_command_t;



/**********************
*  GLOBAL PROTOTYPES
 **********************/
void sgfx_display_register_instance(struct sgfx_display * self, 
                            const struct sgfx_display_drawing ** drawing, 
                            const struct sgfx_display_backlight ** backlight);




#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_H*/


/******************************* (END OF FILE) *********************************/


