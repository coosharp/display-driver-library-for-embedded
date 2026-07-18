/**
 * @file backlight.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_backlight.h"
#include "sgfx_log.h"
/*********************
 *      MACROS
 *********************/
#if SGFX_LOG_BACKLIGHT_ENABLE
    #define LOG_TRACE_BACKLIGHT(fmt, ...)   SGFX_LOG_TRACE(fmt, ##__VA_ARGS__)
    #define LOG_INFO_BACKLIGHT(fmt, ...)    SGFX_LOG_INFO(fmt, ##__VA_ARGS__)
    #define LOG_WARN_BACKLIGHT(fmt, ...)    SGFX_LOG_WARN(fmt, ##__VA_ARGS__)
    #define LOG_ERROR_BACKLIGHT(fmt, ...)   SGFX_LOG_ERROR(fmt, ##__VA_ARGS__)
#else 
    #define LOG_TRACE_BACKLIGHT(fmt, ...)   do{} while(0)
    #define LOG_INFO_BACKLIGHT(fmt, ...)    do{} while(0)
    #define LOG_WARN_BACKLIGHT(fmt, ...)    do{} while(0)
    #define LOG_ERROR_BACKLIGHT(fmt, ...)   do{} while(0)
#endif
/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static const struct sgfx_display_backlight tDisplayBacklight = 
{
    .set_backlight_state        = sgfx_backlight_set_state,
    .get_backlight_state        = sgfx_backlight_get_state,
    .set_backlight_brightness   = sgfx_backlight_set_brightness,
    .get_backlight_brightness   = sgfx_backlight_get_brightness,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void sgfx_backlight_register(struct sgfx_backlight * self)
{
    self->display_backlight = &tDisplayBacklight;
}

void sgfx_backlight_set_state(const struct sgfx_display_backlight ** display_backlight, uint8_t state)
{
    const struct sgfx_backlight * self = (const struct sgfx_backlight *)display_backlight;

    if(state) {
        backlight_set_gpio_level_fn_t fn = self->set_gpio_level;

        if(fn) {
            fn();
        }
        else {
            LOG_WARN_BACKLIGHT("Backlight set gpio function not implemented!");
        }
    }
    else {
        backlight_clear_gpio_level_fn_t fn = self->clear_gpio_level;

        if(fn) {
            fn();
        }
        else {
            LOG_WARN_BACKLIGHT("Backlight clear gpio function not implemented!");
        }
    }

    
}

void sgfx_backlight_get_state(const struct sgfx_display_backlight ** display_backlight, uint8_t * state)
{
    const struct sgfx_backlight * self = (const struct sgfx_backlight *)display_backlight;

    *state = self->backlight_variable.state;
}

void sgfx_backlight_set_brightness(const struct sgfx_display_backlight ** display_backlight, uint8_t brightness)
{
    const struct sgfx_backlight * self = (const struct sgfx_backlight *)display_backlight;

    backlight_set_pwm_duty_fn_t fn = self->set_pwm_duty;

    if(fn) {
        fn(brightness);
    }
    else {
        LOG_WARN_BACKLIGHT("Backlight set brightness function not implemented!");
    }
}

void sgfx_backlight_get_brightness(const struct sgfx_display_backlight ** display_backlight, uint8_t * brightness)
{
    const struct sgfx_backlight * self = (const struct sgfx_backlight *)display_backlight;

    *brightness = self->backlight_variable.brightness;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 













