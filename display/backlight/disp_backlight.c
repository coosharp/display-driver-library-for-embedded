/**
 * @file disp_backlight.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "../display.h"
#include "../display_conf.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void disp_backlight_register_instance(struct display * self, const struct disp_backlight ** backlight)
{
    self->backlight = backlight;
}

void disp_backlight_turn_on(const struct display * self)
{
    turn_on_fn_t fn = (*self->backlight)->turn_on;

    if(fn) 
        fn(self->backlight);  
}

void disp_backlight_turn_off(const struct display * self)
{
    turn_off_fn_t fn = (*self->backlight)->turn_off;

    if(fn)
        fn(self->backlight);
}

void disp_backlight_set_brightness(const struct display * self, uint8_t brightness)
{
    set_brightness_fn_t fn = (*self->backlight)->set_brightness;
    if(fn)
        fn(self->backlight, brightness);
}


/******************************* (END OF FILE) *********************************/



 








