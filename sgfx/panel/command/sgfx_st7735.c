/**
 * @file sgfx_st7735.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_st7735.h"
#include "sgfx_config.h"
#include "sgfx_log.h"
/*********************
 *      MACROS
 *********************/
#if SGFX_LOG_ST7735_ENABLE
    #define LOG_TRACE_ST7735(fmt, ...)  SGFX_LOG_TRACE(fmt, ##__VA_ARGS__)
    #define LOG_INFO_ST7735(fmt, ...)   SGFX_LOG_INFO(fmt, ##__VA_ARGS__)
    #define LOG_WARN_ST7735(fmt, ...)   SGFX_LOG_WARN(fmt, ##__VA_ARGS__)
    #define LOG_ERROR_ST7735(fmt, ...)  SGFX_LOG_ERROR(fmt, ##__VA_ARGS__)
#else
    #define LOG_TRACE_ST7735(fmt, ...)  do{} while(0)
    #define LOG_INFO_ST7735(fmt, ...)   do{} while(0)
    #define LOG_WARN_ST7735(fmt, ...)   do{} while(0)
    #define LOG_ERROR_ST7735(fmt, ...)  do{} while(0)
#endif
/**********************
 *      DEFINES
 **********************/ 

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
static void _st7735_delay_ms(const struct sgfx_lcd_drawing ** drawing, uint32_t nms);
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
    ST7735_FRAME_RATE_CTRL3,        6,  0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C,
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

static const struct sgfx_lcd_drawing tLcdDrawingST7735 = 
{
    .fill_point     = sgfx_st7735_fill_point,
    .fill_rectangle = sgfx_st7735_fill_rectangle,
    .flush          = sgfx_st7735_flush,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void sgfx_st7735_register(struct sgfx_st7735 * self, const struct sgfx_lcd_driver ** driver)
{
    self->lcd_drawing = &tLcdDrawingST7735;
    self->lcd_driver = driver;
}

void sgfx_st7735_init(struct sgfx_st7735 * self, 
                      uint16_t width,
                      uint16_t height,
                      uint16_t rotation)
{
    self->lcd_variable.width = width;
    self->lcd_variable.height = height;
    self->lcd_variable.rotation = rotation;

    sgfx_st7735_prepare(&self->lcd_drawing);

    _st7735_set_orientation(&self->lcd_drawing, rotation);
}


void sgfx_st7735_prepare(const struct sgfx_lcd_drawing ** drawing)
{
    LOG_TRACE_ST7735("Begin!");

    uint8_t cmd = 0;
    uint8_t num = 0;
    uint32_t index = 0;
    const uint8_t * addr = &ucInitCmdList[0]; 

    _st7735_start_transfer(drawing);

    for(;index < sizeof(ucInitCmdList) / sizeof(ucInitCmdList[0]);) {
        cmd = addr[index++];
        num = addr[index++];
        if(cmd == ST7735_DELAY) {
            _st7735_delay_ms(drawing, num);
        }
        else {
            _st7735_write_reg(drawing, cmd);
            _st7735_send_data(drawing, addr, num);
            index += num;
        }
    }

    _st7735_stop_transfer(drawing);

    LOG_TRACE_ST7735("End!");
}


void sgfx_st7735_fill_point(const struct sgfx_lcd_drawing ** drawing, 
                            uint16_t x,
                            uint16_t y,
                            uint32_t color)
{
    uint16_t pixel = 0;

    /* Exchange LSB and MSB to fit LCD specification */
    pixel = (uint16_t)((uint16_t)color << 8);
    pixel |= (uint16_t)((uint16_t)(color >> 8));

    _st7735_set_cursor(drawing, x, y);

    _st7735_start_transfer(drawing);

    _st7735_send_data(drawing, (uint8_t *)&pixel, 2);

    _st7735_stop_transfer(drawing);
}

void sgfx_st7735_fill_rectangle(const struct sgfx_lcd_drawing ** drawing,
                                uint16_t x,
                                uint16_t y,
                                uint16_t w,
                                uint16_t h,
                                uint32_t color)
{
    uint16_t pixel = 0;
    uint8_t pixel_bytes[2] = {0};
    uint32_t pixel_count = 0U;
    uint32_t index = 0U;

    if((w == 0U) || (h == 0U)) {
        return;
    }

    /* Exchange LSB and MSB to fit LCD specification */
    pixel = (uint16_t)((uint16_t)color << 8U);
    pixel |= (uint16_t)((uint16_t)(color >> 8U));

    pixel_bytes[0] = (uint8_t)(pixel & 0xFFU);
    pixel_bytes[1] = (uint8_t)(pixel >> 8U);

    pixel_count = ((uint32_t)w * (uint32_t)h);

    _st7735_set_window(drawing, x, y, w, h);

    _st7735_start_transfer(drawing);

    for(index = 0U; index < pixel_count; index++) {
        _st7735_send_data(drawing, pixel_bytes, sizeof(pixel_bytes));
    }

    _st7735_stop_transfer(drawing);
}

void sgfx_st7735_flush(const struct sgfx_lcd_drawing ** drawing,
                       uint16_t x1, 
                       uint16_t y1, 
                       uint16_t x2, 
                       uint16_t y2,
                       const void * src)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;
    uint16_t width = (uint16_t)(x2 - x1 + 1U);
    uint16_t height = (uint16_t)(y2 - y1 + 1U);
    uint32_t pixel_count = ((uint32_t)width * (uint32_t)height);

    if((src == NULL) || (x1 > x2) || (y1 > y2)) {
        return;
    }


    _st7735_set_window(drawing, x1, y1, width, height);

    _st7735_start_transfer(drawing);
 
    sgfx_lcd_copy_data(self->lcd_driver, src, pixel_count);

    _st7735_stop_transfer(drawing);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _st7735_start_transfer(const struct sgfx_lcd_drawing ** drawing)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    sgfx_lcd_start_transfer(self->lcd_driver);
}

static void _st7735_stop_transfer(const struct sgfx_lcd_drawing ** drawing)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    sgfx_lcd_stop_transfer(self->lcd_driver);
}

static void _st7735_delay_ms(const struct sgfx_lcd_drawing ** drawing, uint32_t nms)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    sgfx_lcd_delay_ms(self->lcd_driver, nms);
}

static void _st7735_write_reg(const struct sgfx_lcd_drawing ** drawing, uint8_t reg)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    sgfx_lcd_write_command(self->lcd_driver, reg);
}

static void _st7735_send_data(const struct sgfx_lcd_drawing ** drawing,
                              const uint8_t * src,
                              size_t size)
{
    const struct sgfx_st7735 * self = (const struct sgfx_st7735 *)drawing;

    sgfx_lcd_write_data8(self->lcd_driver, src, size);
}

static void _st7735_set_cursor(const struct sgfx_lcd_drawing ** drawing, 
                               uint16_t x, 
                               uint16_t y)
{
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



 







