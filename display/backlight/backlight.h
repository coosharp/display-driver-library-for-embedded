/**
 * @file backlight.h
 *
 */
  
#ifndef _BACKLIGHT_H
#define _BACKLIGHT_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../display.h"
#include "backlight_ctrl.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct backlight
{
    const struct display_backlight * backlight;
    const struct backlight_ctrl ** ctrl;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void backlight_register(struct backlight * self, const struct backlight_ctrl ** ctrl);
void backlight_enable(const struct display_backlight ** backlight);
void backlight_disable(const struct display_backlight ** backlight);
void backlight_set_brightness(const struct display_backlight ** backlight, uint8_t brightness);
 

#ifdef __cplusplus
}
#endif

#endif /*_BACKLIGHT_H*/


/******************************* (END OF FILE) *********************************/







