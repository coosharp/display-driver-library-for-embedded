/**
 * @file disp_backlight_port.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "../backlight/disp_backlight.h"
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void turn_on_backlight(const disp_backlight_t ** backlight)
{
    (void)backlight;
    printf("turn_on_backlight\n");
}

static void turn_off_backlight(const disp_backlight_t ** backlight)
{
    (void)backlight;
    printf("turn_off_backlight\n");
}

static void set_backlight_brightness(const disp_backlight_t ** backlight, uint8_t brightness)
{
    (void)backlight;
    printf("set_backlight_brightness: %d\n", brightness);
}

static const struct disp_backlight backlight = 
{
    .turn_on = turn_on_backlight,
    .turn_off = turn_off_backlight,
    .set_brightness = set_backlight_brightness,
};

static const struct disp_backlight * backlight_instance = &backlight;

const disp_backlight_t ** disp_port_get_backlight_instance(void)
{
    return &backlight_instance;
}

/******************************* (END OF FILE) *********************************/



 








