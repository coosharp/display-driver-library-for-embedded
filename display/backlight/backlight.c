/**
 * @file backlight.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "backlight.h"
#include "display.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static const struct display_backlight backlight_driver = 
{
    NULL
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void backlight_register(struct backlight * self, const struct backlight_ctrl ** ctrl)
{
    self->backlight = &backlight_driver;
    self->ctrl = ctrl;
}

void backlight_enable(const struct display_backlight ** backlight)
{
    const struct backlight * self = (const struct backlight *)backlight;

    backlight_gpio_set_level(self->ctrl);
}

void backlight_disable(const struct display_backlight ** backlight)
{
    const struct backlight * self = (const struct backlight *)backlight;

    backlight_gpio_clear_level(self->ctrl);
}

void backlight_set_brightness(const struct display_backlight ** backlight, uint8_t brightness)
{
    const struct backlight * self = (const struct backlight *)backlight;

    backlight_pwm_set_duty(self->ctrl, brightness);
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 













