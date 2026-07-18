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
#include "sgfx_display.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/

typedef void (* backlight_set_gpio_level_fn_t)(void);
typedef void (* backlight_clear_gpio_level_fn_t)(void);
typedef void (* backlight_set_pwm_duty_fn_t)(uint8_t brightness);

struct sgfx_backlight_variable
{
    uint8_t state;
    uint8_t brightness;
};

struct sgfx_backlight
{
    const struct sgfx_display_backlight * display_backlight;

    backlight_set_gpio_level_fn_t   set_gpio_level;
    backlight_clear_gpio_level_fn_t clear_gpio_level;
    backlight_set_pwm_duty_fn_t     set_pwm_duty;

    struct sgfx_backlight_variable backlight_variable;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void sgfx_backlight_register(struct sgfx_backlight * self);
void sgfx_backlight_set_state(const struct sgfx_display_backlight ** display_backlight, uint8_t state);
void sgfx_backlight_get_state(const struct sgfx_display_backlight ** display_backlight, uint8_t * state);
void sgfx_backlight_set_brightness(const struct sgfx_display_backlight ** display_backlight, uint8_t brightness);
void sgfx_backlight_get_brightness(const struct sgfx_display_backlight ** display_backlight, uint8_t * brightness);



#ifdef __cplusplus
}
#endif

#endif /*_BACKLIGHT_H*/


/******************************* (END OF FILE) *********************************/







