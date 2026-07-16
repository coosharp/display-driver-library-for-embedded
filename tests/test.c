#include "sgfx_display.h"
#include "sgfx_spi.h"
#include "sgfx_st7735.h"
#include "sgfx_lcd.h"

int main(void)
{
    struct sgfx_spi spi_instance = 
    {
        .chip_select_enable = NULL,
        .chip_select_disable = NULL,
    };
    sgfx_spi_register(&spi_instance);

    struct sgfx_st7735 st7735_instance;
    sgfx_st7735_register(&st7735_instance, &spi_instance.driver);

    struct sgfx_lcd lcd_instance;
    sgfx_lcd_register(&lcd_instance, &st7735_instance.lcd_drawing);

    struct sgfx_display display_instance;
    sgfx_display_register(&display_instance, &lcd_instance.display_drawing, NULL);

    return 0;
}