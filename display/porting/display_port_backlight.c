/**
 * @file display_port_backlight.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "display_port_backlight.h"
#include "display_log.h"

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void set_gpio_level(const struct backlight_ctrl ** ctrl)
{
    const struct display_port_backlight * self = (const struct display_port_backlight *)ctrl;
    
    (void)self;

    LOG_TRACE_DISPLAY("Turn on backlight");
} 

static void clear_gpio_level(const struct backlight_ctrl ** ctrl)
{
    const struct display_port_backlight * self = (const struct display_port_backlight *)ctrl;
    
    (void)self;

    LOG_TRACE_DISPLAY("Turn off backlight");
}

static void set_pwm_duty(const struct backlight_ctrl ** ctrl, uint8_t brightness)
{
    const struct display_port_backlight * self = (const struct display_port_backlight *)ctrl;
    
    (void)self;

    LOG_TRACE_DISPLAY("Set backlight brightness: %d", brightness);
}

static const struct backlight_ctrl ctrl = 
{
    NULL
};


void display_port_backlight_register(struct display_port_backlight * self, void * platform_data)
{
    self->ctrl = &ctrl;
    self->platform_data = platform_data;

    LOG_TRACE_DISPLAY("");
}

/******************************* (END OF FILE) *********************************/



 







