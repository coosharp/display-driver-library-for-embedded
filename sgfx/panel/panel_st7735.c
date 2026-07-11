
  
/*********************
 *      INCLUDES
 *********************/
#include <string.h>
#include "panel_st7735.h"
#include "display_log.h"
/**********************
 *   STATIC VARIABLES
 **********************/ 
static const struct display_painter painter_driver = 
{
    NULL,
};


// static const uint8_t st7735_mad_ctrl_params[] = {ST7735_ORIENTATION};

static void _st7735_write_reg(const struct st7735 * self, 
                              uint8_t reg,  
                              const uint8_t * data, 
                              size_t size);


/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void st7735_register(struct st7735 * self, 
                     const struct panel_spi ** spi,
                     const struct st7735_context * context)
{
    self->painter = &painter_driver;
    self->spi = spi;


    self->context.width = context->width;
    self->context.height = context->height;
    self->context.rotation = context->rotation;
    strncpy(self->context.color_mode, context->color_mode, 6);
    self->context.color_mode[7] = '\0';

    LOG_TRACE_DISPLAY("ST7735 register complete: width = %d, height = %d, rotation = %d, color_mode = %s", 
                      self->context.width, self->context.height, self->context.rotation, self->context.color_mode);
}

void st7735_set_orientation(const struct display_painter ** painter, uint16_t rotation)
{
    const struct st7735 * self = (const struct st7735 *)painter;

    uint8_t mad_ctrl_param[1] = {0};

    if(rotation == 0) {
        mad_ctrl_param[0] = ST7735_ORIENTATION_PORTRAIT;
    }
    else if(rotation == 90) {
        mad_ctrl_param[0] = ST7735_ORIENTATION_LANDSCAPE;
    }
    else if(rotation == 180) {
        mad_ctrl_param[0] = ST7735_ORIENTATION_PORTRAIT_ROT180;
    }
    else if(rotation == 270) {
        mad_ctrl_param[0] = ST7735_ORIENTATION_LANDSCAPE_ROT180;
    }
    else {
        LOG_ERROR_DISPLAY("Invalid rotation value: %d. Supported values are: 0, 90, 180, 270", rotation);
        return;
    }

    panel_spi_select(self->spi, 1);

    _st7735_write_reg(self, ST7735_MADCTL, mad_ctrl_param, sizeof(mad_ctrl_param));

    panel_spi_select(self->spi, 0);
}


void st7735_prepare(const struct display_painter ** painter)
{
    const struct st7735 * self = (const struct st7735 *)painter;


}

void st7735_set_cursor(const struct display_painter ** painter, 
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

void st7735_set_window(const struct display_painter ** painter, 
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

void st7735_fill_point(const struct display_painter ** painter, 
                       uint16_t x, 
                       uint16_t y, 
                       uint32_t color)
{

}





/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _st7735_write_reg(const struct st7735 * self, 
                              )
{
    panel_spi_write_command(self->spi, &reg, 1);
    panel_spi_write_data8(self->spi, data, size);
}


/******************************* (END OF FILE) *********************************/



 







