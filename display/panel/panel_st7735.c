/**
 * @file panel_st7735.c
 *
 */
  
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

static const uint8_t st7735_sleep_out_params[] = {0x00};
static const uint8_t st7735_frame_rate_ctrl1_params[] = {0x05, 0x3C, 0x3C};
static const uint8_t st7735_frame_rate_ctrl2_params[] = {0x05, 0x3C, 0x3C};
static const uint8_t st7735_frame_rate_ctrl3_params[] = {0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C};
static const uint8_t st7735_frame_inversion_ctrl_params[] = {0x03};
static const uint8_t st7735_pwr_ctrl1_params[] = {0x28, 0x08, 0x04};
static const uint8_t st7735_pwr_ctrl2_params[] = {0xC0};
static const uint8_t st7735_pwr_ctrl3_params[] = {0x0D, 0x00};
static const uint8_t st7735_pwr_ctrl4_params[] = {0x8D, 0x2A};
static const uint8_t st7735_pwr_ctrl5_params[] = {0x8D, 0xEE};
static const uint8_t st7735_vcomh_vcoml_ctrl1_params[] = {0x1A};
static const uint8_t st7735_color_mode_params[] = {ST7735_FORMAT_RBG444, ST7735_FORMAT_RBG565, ST7735_FORMAT_RBG666};
static const uint8_t st7735_pv_gamma_ctrl_params[] = {0x04, 0x22, 0x07, 0x0A, 0x2E, 0x30, 0x25, 0x2A, 0x28, 0x26, 0x2E, 0x3A, 0x00, 0x01, 0x03, 0x13};
static const uint8_t st7735_nv_gamma_ctrl_params[] = {0x04, 0x16, 0x06, 0x0D, 0x2D, 0x26, 0x23, 0x27, 0x27, 0x25, 0x2D, 0x3B, 0x01, 0x00, 0x04, 0x13};
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

    panel_spi_select(self->spi, 1);

    _st7735_write_reg(self, ST7735_SW_RESET, NULL, 0);

    _st7735_write_reg(self, ST7735_SLEEP_OUT, st7735_sleep_out_params, sizeof(st7735_sleep_out_params));

    panel_spi_delay_ms(self->spi, 10);

    _st7735_write_reg(self, ST7735_DISPLAY_OFF, NULL, 0);

    _st7735_write_reg(self, ST7735_FRAME_RATE_CTRL1, st7735_frame_rate_ctrl1_params, sizeof(st7735_frame_rate_ctrl1_params));

    _st7735_write_reg(self, ST7735_FRAME_RATE_CTRL2, st7735_frame_rate_ctrl2_params, sizeof(st7735_frame_rate_ctrl2_params));

    _st7735_write_reg(self, ST7735_FRAME_RATE_CTRL3, st7735_frame_rate_ctrl3_params, sizeof(st7735_frame_rate_ctrl3_params));

    _st7735_write_reg(self, ST7735_FRAME_INVERSION_CTRL, st7735_frame_inversion_ctrl_params, sizeof(st7735_frame_inversion_ctrl_params));

    _st7735_write_reg(self, ST7735_PWR_CTRL1, st7735_pwr_ctrl1_params, sizeof(st7735_pwr_ctrl1_params));

    _st7735_write_reg(self, ST7735_PWR_CTRL2, st7735_pwr_ctrl2_params, sizeof(st7735_pwr_ctrl2_params));

    _st7735_write_reg(self, ST7735_PWR_CTRL3, st7735_pwr_ctrl3_params, sizeof(st7735_pwr_ctrl3_params));

    _st7735_write_reg(self, ST7735_PWR_CTRL4, st7735_pwr_ctrl4_params, sizeof(st7735_pwr_ctrl4_params));

    _st7735_write_reg(self, ST7735_PWR_CTRL5, st7735_pwr_ctrl5_params, sizeof(st7735_pwr_ctrl5_params));

    _st7735_write_reg(self, ST7735_VCOMH_VCOML_CTRL1, st7735_vcomh_vcoml_ctrl1_params, sizeof(st7735_vcomh_vcoml_ctrl1_params));

    _st7735_write_reg(self, ST7735_DISPLAY_INVERSION_OFF, NULL, 0);

    _st7735_write_reg(self, ST7735_PV_GAMMA_CTRL, st7735_pv_gamma_ctrl_params, sizeof(st7735_pv_gamma_ctrl_params));

    _st7735_write_reg(self, ST7735_NV_GAMMA_CTRL, st7735_nv_gamma_ctrl_params, sizeof(st7735_nv_gamma_ctrl_params));
   
    _st7735_write_reg(self, ST7735_NORMAL_DISPLAY_OFF, NULL, 0);


    if(strcmp(self->context.color_mode, "RGB444") == 0) {
        _st7735_write_reg(self, ST7735_COLOR_MODE, &st7735_color_mode_params[0], 1);
    }
    else if(strcmp(self->context.color_mode, "RGB565") == 0) {
        _st7735_write_reg(self, ST7735_COLOR_MODE, &st7735_color_mode_params[1], 1);
    }
    else if(strcmp(self->context.color_mode, "RGB666") == 0) {
        _st7735_write_reg(self, ST7735_COLOR_MODE, &st7735_color_mode_params[2], 1);
    }
    else {
        LOG_WARN_DISPLAY("Invalid color mode: %s. Supported modes are: RGB444, RGB565, RGB666. Defaulting to RGB565", self->context.color_mode);
        _st7735_write_reg(self, ST7735_COLOR_MODE, &st7735_color_mode_params[1], 1);
    }
    

    _st7735_write_reg(self, ST7735_DISPLAY_ON, NULL, 0);
    
    panel_spi_select(self->spi, 0);
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
static void _st7735_write_reg(const struct st7735 * self, 
                              uint8_t reg, 
                              const uint8_t * data, 
                              size_t size)
{
    panel_spi_write_command(self->spi, &reg, 1);
    panel_spi_write_data8(self->spi, data, size);
}


/******************************* (END OF FILE) *********************************/



 







