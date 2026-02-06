#include "display.h"
#include "panel_st7735.h"



int main(void)
{
    const disp_backlight_t ** backlight = disp_port_get_backlight_instance();

    struct display st7735_driver;
    disp_panel_register_instance(&st7735_driver, DISP_PANEL_ST7735);
    disp_backlight_register_instance(&st7735_driver, backlight);

    disp_backlight_turn_on(&st7735_driver);
    disp_backlight_set_brightness(&st7735_driver, 50);

    disp_painter_fill_point(&st7735_driver, 20, 30, 0xFFFF);

    return 0;
}