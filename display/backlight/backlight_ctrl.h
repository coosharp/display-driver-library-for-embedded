/**
 * @file backlight_ctrl.h
 *
 */
  
#ifndef _BACKLIGHT_CTRL_H
#define _BACKLIGHT_CTRL_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
typedef struct backlight_ctrl backlight_ctrl_t;
typedef void (* gpio_set_level_fn_t)(const backlight_ctrl_t ** self);
typedef void (* gpio_clear_level_fn_t)(const backlight_ctrl_t ** self);
typedef void (* pwm_set_duty_fn_t)(const backlight_ctrl_t ** self, uint32_t duty);

struct backlight_ctrl
{
    gpio_set_level_fn_t gpio_set_level;
    gpio_clear_level_fn_t gpio_clear_level;
    pwm_set_duty_fn_t pwm_set_duty;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void backlight_gpio_set_level(const struct backlight_ctrl ** self);
void backlight_gpio_clear_level(const struct backlight_ctrl ** self);
void backlight_pwm_set_duty(const struct backlight_ctrl ** self, uint8_t duty);

#ifdef __cplusplus
}
#endif

#endif /*_BACKLIGHT_CTRL_H*/


/******************************* (END OF FILE) *********************************/


