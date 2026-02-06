/**
 * @file disp_backlight.h
 *
 */
  
#ifndef _DISP_BACKLIGHT_H
#define _DISP_BACKLIGHT_H


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
typedef struct disp_backlight disp_backlight_t;
typedef void (* turn_on_fn_t)(const disp_backlight_t ** self);
typedef void (* turn_off_fn_t)(const disp_backlight_t ** self);
typedef void (* set_brightness_fn_t)(const disp_backlight_t ** self, uint8_t brightness);

struct disp_backlight
{
    turn_on_fn_t turn_on;
    turn_off_fn_t turn_off;
    set_brightness_fn_t set_brightness;
};
 

#ifdef __cplusplus
}
#endif

#endif /*_DISP_BACKLIGHT_H*/


/******************************* (END OF FILE) *********************************/


