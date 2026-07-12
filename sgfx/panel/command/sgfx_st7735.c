/**
 * @file sgfx_st7735.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_st7735.h"
#include "sgfx_config.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *      DEFINES
 **********************/ 


#define LOG_TRACE_ST7735
#define LOG_INFO_ST7735
#define LOG_WARN_ST7735
#define LOG_ERROR_ST7735


#define ST7735_DELAY    (0x80)


#if     SGFX_LCD_COLOR_MODE == SGFX_COLOR_RGB444
    #define ST7735_COLOR_FORMAT ST7735_FORMAT_RBG444

#elif   SGFX_LCD_COLOR_MODE == SGFX_COLOR_RGB565
    #define ST7735_COLOR_FORMAT ST7735_FORMAT_RBG565

#elif   SGFX_LCD_COLOR_MODE == SGFX_COLOR_RGB666
    #define ST7735_COLOR_FORMAT ST7735_FORMAT_RBG666

#else   
    #pragma message()
    #define ST7735_COLOR_FORMAT
#endif

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _st7735_start_transfer(const struct sgfx_lcd_drawing ** drawing);
static void _st7735_stop_transfer(const struct sgfx_lcd_drawing ** drawing);
static void _st7735_delay_ms(const struct sgfx_lcd_drawing ** drawing, uint32_t ms);
static void _st7735_write_reg(const struct sgfx_lcd_drawing ** drawing, uint8_t reg);
static void _st7735_send_data(const struct sgfx_lcd_drawing ** drawing,
                              const uint8_t * src,
                              size_t size);
static void _st7735_set_cursor(const struct sgfx_lcd_drawing ** drawing, 
                               uint16_t x, 
                               uint16_t y);
static void _st7735_set_window(const struct sgfx_lcd_drawing ** drawing, 
                               uint16_t x, 
                               uint16_t y, 
                               uint16_t w, 
                               uint16_t h);
static void _st7735_set_orientation(const struct sgfx_lcd_drawing ** drawing, uint16_t rotation);
/**********************
 *  STATIC VARIABLES
 **********************/
static const uint8_t ucInitCmdList[] = 
{
    ST7735_SW_RESET,                0,
    ST7735_SLEEP_OUT,               1,  0x00,
    ST7735_DELAY,                   10,                
    ST7735_DISPLAY_OFF,             0,
    ST7735_FRAME_RATE_CTRL1,        3,  0x05, 0x3C, 0x3C,
    ST7735_FRAME_RATE_CTRL2,        3,  0x05, 0x3C, 0x3C,
    ST7735_FRAME_RATE_CTRL3         6,  0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C,
    ST7735_FRAME_INVERSION_CTRL,    1,  0x03,
    ST7735_PWR_CTRL1,               3,  0x28, 0x08, 0x04,
    ST7735_PWR_CTRL2,               1,  0xC0,
    ST7735_PWR_CTRL3,               2,  0x0D, 0x00,
    ST7735_PWR_CTRL4,               2,  0x8D, 0x2A,
    ST7735_PWR_CTRL5,               2,  0x8D, 0xEE,
    ST7735_VCOMH_VCOML_CTRL1,       1,  0x1A,
    ST7735_PV_GAMMA_CTRL,           16, 0x04, 0x22, 0x07, 0x0A, 0x2E, 0x30, 0x25, 0x2A, 0x28, 0x26, 0x2E, 0x3A, 0x00, 0x01, 0x03, 0x13,
    ST7735_NV_GAMMA_CTRL,           16, 0x04, 0x16, 0x06, 0x0D, 0x2D, 0x26, 0x23, 0x27, 0x27, 0x25, 0x2D, 0x3B, 0x01, 0x00, 0x04, 0x13,
    ST7735_DISPLAY_INVERSION_OFF,   0,
    ST7735_NORMAL_DISPLAY_OFF,      0,
    ST7735_COLOR_MODE,              1,   ST7735_COLOR_FORMAT,
    ST7735_DISPLAY_ON,              0,
};

static const struct sgfx_lcd_drawing tDrawing = 
{
    .fill_point = NULL,
};
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void sgfx_st7735_prepare(const struct sgfx_lcd_drawing ** drawing)
{
    uint8_t cmd = 0;
    uint8_t num = 0;
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    _st7735_start_transfer(drawing);

    for(;;) {
        cmd = *ucInitCmdList++;
        num = *ucInitCmdList++;
        if(cmd == ST7735_DELAY) {
            _st7735_delay_ms(drawing, num);
        }
        else if(cmd == ST7735_COLOR_MODE) {

        }
        else {
            _st7735_write_reg(drawing, cmd);
            _st7735_send_data(drawing, ucInitCmdList, num);
        }
    }

    _st7735_stop_transfer(drawing);
}

void sgfx_st7735_fill_point(const struct sgfx_lcd_drawing ** drawing, 
                            uint16_t x,
                            uint16_t y,
                            uint32_t color)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    const struct st7735 * self = (const struct st7735 *)painter;
    uint16_t pixel = 0;

    /* Exchange LSB and MSB to fit LCD specification */
    pixel = (uint16_t)((uint16_t)color << 8);
    pixel |= (uint16_t)((uint16_t)(color >> 8));

    _st7735_set_cursor(drawing, x, y);

    _st7735_start_transfer(drawing);

    _st7735_send_data(drawing, (uint8_t *)&pixel, 2);

    _st7735_stop_transfer(drawing);
}

void sgfx_st7735_fill_rectangle(const struct sgfx_lcd_drawing ** drawing)
{

}

void sgfx_st7735_flush(const struct sgfx_lcd_drawing ** drawing)
{

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _st7735_start_transfer(const struct sgfx_lcd_drawing ** drawing)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;

    sgfx_lcd_start_transfer(self->driver);
}

static void _st7735_stop_transfer(const struct sgfx_lcd_drawing ** drawing)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;

    sgfx_lcd_stop_transfer(self->driver);
}

static void _st7735_delay_ms(const struct sgfx_lcd_drawing ** drawing, uint32_t ms)
{

}

static void _st7735_write_reg(const struct sgfx_lcd_drawing ** drawing, uint8_t reg)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;

    sgfx_lcd_write_command(self->driver, reg);
}

static void _st7735_send_data(const struct sgfx_lcd_drawing ** drawing,
                              const uint8_t * src,
                              size_t size)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;

    sgfx_lcd_write_data8(self->driver, src, size);
}

static void _st7735_set_cursor(const struct sgfx_lcd_drawing ** drawing, 
                               uint16_t x, 
                               uint16_t y)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;
    const uint8_t command[] = {ST7735_CASET, ST7735_RASET, ST7735_RAMWR};
    
    uint8_t x_coord[] = {(x >> 8U), (x & 0xFFU)};
    uint8_t y_coord[] = {(y >> 8U), (y & 0xFFU)};

    _st7735_start_transfer(drawing);

    _st7735_write_reg(drawing, command[0]);
    _st7735_send_data(drawing, x_coord, (sizeof(x_coord)/ sizeof(x_coord[0])));

    _st7735_write_reg(drawing, command[1]);
    _st7735_send_data(drawing, y_coord, (sizeof(y_coord) / sizeof(y_coord[0])));

    _st7735_write_reg(drawing, command[2]);

    _st7735_stop_transfer(drawing);  
}

static void _st7735_set_window(const struct sgfx_lcd_drawing ** drawing, 
                               uint16_t x, 
                               uint16_t y, 
                               uint16_t w, 
                               uint16_t h)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;

    const struct st7735 * self = (const struct st7735 *)painter;
    const uint8_t command[] = {ST7735_CASET, ST7735_RASET, ST7735_RAMWR};

    uint16_t x_start = x;
    uint16_t x_end   = x + w - 1U;
    uint16_t y_start = y;
    uint16_t y_end   = y + h - 1U;

    uint8_t x_coords[4] = {(x_start >> 8U), (x_start & 0xFFU), 
                           (x_end >> 8U),   (x_end & 0xFFU)};
    uint8_t y_coords[4] = {(y_start >> 8U), (y_start & 0xFFU),
                           (y_end >> 8U), (y_end & 0xFFU)};


    _st7735_start_transfer(drawing);

    _st7735_write_reg(drawing, command[0]);
    _st7735_send_data(drawing, x_coords, (sizeof(x_coords)/ sizeof(x_coords[0])));

    _st7735_write_reg(drawing, command[1]);
    _st7735_send_data(drawing, y_coords, (sizeof(y_coords) / sizeof(y_coords[0])));

    _st7735_write_reg(drawing, command[2]);

    _st7735_stop_transfer(drawing); 
}

static void _st7735_set_orientation(const struct sgfx_lcd_drawing ** drawing, uint16_t rotation)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735)drawing;

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
        LOG_ERROR_ST7735("Invalid rotation value: %d. Supported values are: 0, 90, 180, 270", rotation);
        return;
    }

    _st7735_start_transfer(drawing);

    _st7735_write_reg(drawing, ST7735_MADCTL);
    _st7735_send_data(drawing, mad_ctrl_param, sizeof(mad_ctrl_param));

    _st7735_stop_transfer(drawing);    
}


/******************************* (END OF FILE) *********************************/



 







