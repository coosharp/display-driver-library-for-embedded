#include "display.h"
#include "panel_st7735.h"
#include "panel_com.h"
#include "backlight.h"
#include "backlight_ctrl.h"
#include "display_port_spi.h"
#include "display_port_backlight.h"


extern void display_register_instance(struct display * self, 
                               const struct display_painter ** painter, 
                               const struct display_backlight ** backlight);


int main(void)
{
    struct display_port_spi st7735_spi_instance;
    display_port_spi_register(&st7735_spi_instance, NULL);

    struct display_port_backlight backlight_ctrl_instance;
    display_port_backlight_register(&backlight_ctrl_instance, NULL);
    
    struct st7735 st7735_instance;
    struct st7735_context st7735_ctx = {
        .width = 128,
        .height = 160,
        .rotation = 0,
        .color_mode = "RGB565"
    };
    st7735_register(&st7735_instance, &st7735_spi_instance.spi, &st7735_ctx);

    struct backlight backlight_instance;
    backlight_register(&backlight_instance, &backlight_ctrl_instance.ctrl);

    struct display st7735_display;
    display_register_instance(&st7735_display, &st7735_instance.painter, &backlight_instance.backlight);


    return 0;
}