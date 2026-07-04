/**
 * @file backlight_ctrl.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "backlight_ctrl.h"
#include "display_log.h"
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

    if(fn) {
        fn(self);
    }
    else {
        LOG_WARN_DISPLAY("GPIO set level function not implemented!");
    }
}

void backlight_gpio_clear_level(const struct backlight_ctrl ** self)
{
    gpio_clear_level_fn_t fn = (*self)->gpio_clear_level;

    if(fn) {
        fn(self);
    }
    else {
        LOG_WARN_DISPLAY("GPIO clear level function not implemented!");
    }
        
}

void backlight_pwm_set_duty(const struct backlight_ctrl ** self, uint8_t duty)
{
    pwm_set_duty_fn_t fn = (*self)->pwm_set_duty;

    if(fn) {
        fn(self, duty);
    }
    else {
        LOG_WARN_DISPLAY("PWM set duty function not implemented!");
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 





