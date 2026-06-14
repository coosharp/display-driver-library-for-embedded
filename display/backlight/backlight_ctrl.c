/**
 * @file backlight_ctrl.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "backlight_ctrl.h"
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

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void backlight_gpio_set_level(const struct backlight_ctrl ** self)
{
    gpio_set_level_fn_t fn = (*self)->gpio_set_level;

    if(fn)
        fn(self);
}

void backlight_gpio_clear_level(const struct backlight_ctrl ** self)
{
    gpio_clear_level_fn_t fn = (*self)->gpio_clear_level;

    if(fn)
        fn(self);
}

void backlight_pwm_set_duty(const struct backlight_ctrl ** self, uint8_t duty)
{
    pwm_set_duty_fn_t fn = (*self)->pwm_set_duty;

    if(fn)
        fn(self, duty);
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 





