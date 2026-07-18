#include "sgfx_display.h"
#include "sgfx_spi.h"
#include "sgfx_st7735.h"
#include "sgfx_lcd.h"
#include "sgfx_backlight.h"

int main(void)
{
    struct sgfx_spi spi_instance = {0};
    sgfx_spi_register(&spi_instance);

    struct sgfx_st7735 st7735_instance;
    sgfx_st7735_register(&st7735_instance, &spi_instance.driver);

    struct sgfx_lcd lcd_instance;
    sgfx_lcd_register(&lcd_instance, &st7735_instance.lcd_drawing);

    struct sgfx_backlight backlight_instance = {0};
    sgfx_backlight_register(&backlight_instance);

    struct sgfx_display display_instance;
    sgfx_display_register(&display_instance, &lcd_instance.display_drawing, &backlight_instance.display_backlight);

    sgfx_st7735_init(&st7735_instance, 160, 128, 0);

    sgfx_display_set_backlight_state(&display_instance, 1);

    return 0;
}