/**
 * @file panel_st7735.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "panel_st7735.h"
/**********************
 *   STATIC VARIABLES
 **********************/ 
static const struct disp_painter painter_driver = 
{
    .fill_point = st7735_fill_point,
};
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void st7735_register(struct st7735 * self, const struct panel_spi ** spi)
{
    self->painter = &st7735_painter;
    self->spi = spi;
}

void st7735_prepare()
{
    
}

void st7735_set_cursor(const struct disp_painter ** painter, 
                       uint16_t x, 
                       uint16_t y)
{
    const struct st7735 * self = (const struct st7735 *)painter;
    const uint8_t command[] = {ST7735_CASET, ST7735_RASET, ST7735_RAMWR};
    uint16_t data[] = {x, y};

    panel_spi_select(self->spi, 1);

    panel_spi_write_command(self->spi, &command[0], 1);
    panel_spi_write_data16(self->spi, &data[0], 1);

    panel_spi_write_command(self->spi, &command[1], 1);
    panel_spi_write_data16(self->spi, &data[1], 1);

    panel_spi_write_command(self->spi, &command[2], 1);

    panel_spi_select(self->spi, 0);
}

void st7735_set_window(const struct disp_painter ** painter, 
                       uint16_t x, 
                       uint16_t y, 
                       uint16_t w, 
                       uint16_t h)
{
    const struct st7735 * self = (const struct st7735 *)painter;
    const uint8_t command[] = {ST7735_CASET, ST7735_RASET, ST7735_RAMWR};
    uint16_t data[] = {x, y, x + w - 1, y + h - 1};

    panel_spi_select(self->spi, 1);

    panel_spi_write_command(self->spi, &command[0], 1);
    panel_spi_write_data16(self->spi, &data[0], 1);
    panel_spi_write_data16(self->spi, &data[2], 1);

    panel_spi_write_command(self->spi, &command[1], 1);
    panel_spi_write_data16(self->spi, &data[1], 1);
    panel_spi_write_data16(self->spi, &data[3], 1);

    panel_spi_write_command(self->spi, &command[2], 1);

    panel_spi_select(self->spi, 0);
}

void st7735_fill_point(const struct disp_painter ** painter, 
                       uint16_t x, 
                       uint16_t y, 
                       uint32_t color)
{
    const struct st7735 * self = (const struct st7735 *)painter;
    uint16_t data[] = {color};

    st7735_set_cursor(painter, x, y);

    panel_spi_select(self->spi, 1);

    panel_spi_write_data16(self->spi, &data[0], 1);

    panel_spi_select(self->spi, 0);
}





/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







