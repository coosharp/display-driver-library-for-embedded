/**
 * @file sgfx_lcd.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_lcd.h"
#include "sgfx_log.h"
/*********************
 *      MACROS
 *********************/
#if SGFX_LOG_LCD_ENABLE
    #define LOG_TRACE_LCD(fmt, ...)     SGFX_LOG_TRACE(fmt, ##__VA_ARGS__)
    #define LOG_INFO_LCD(fmt, ...)      SGFX_LOG_INFO(fmt, ##__VA_ARGS__)
    #define LOG_WARN_LCD(fmt, ...)      SGFX_LOG_WARN(fmt, ##__VA_ARGS__)
    #define LOG_ERROR_LCD(fmt, ...)     SGFX_LOG_ERROR(fmt, ##__VA_ARGS__)
#else
    #define LOG_TRACE_LCD(fmt, ...)     do{} while(0)
    #define LOG_INFO_LCD(fmt, ...)      do{} while(0)
    #define LOG_WARN_LCD(fmt, ...)      do{} while(0)
    #define LOG_ERROR_LCD(fmt, ...)     do{} while(0)
#endif



/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
int sgfx_lcd_start_transfer(const struct sgfx_lcd_driver ** driver)
{
    lcd_start_transfer_fn_t fn = (*driver)->start_transfer;

    if(fn) {
        LOG_TRACE_LCD("Start to transfer!");
        return fn(driver);
    }
    else {
        LOG_WARN_LCD("Start transfer function not implemented!");
        return 0;
    }
}

int sgfx_lcd_stop_transfer(const struct sgfx_lcd_driver ** driver)
{
    lcd_stop_transfer_fn_t fn = (*driver)->stop_transfer;

    if(fn) {
        LOG_TRACE_LCD("Stop to transfer!");
        return fn(driver);
    }
    else {
        LOG_WARN_LCD("Stop transfer function not implemented!");
        return 0;
    }
}

int sgfx_lcd_write_command(const struct sgfx_lcd_driver ** driver, uint8_t command)
{
    lcd_write_command_fn_t fn = (*driver)->write_command;

    if(fn) {
        LOG_TRACE_LCD("LCD write command: 0x%02x", command);
        return fn(driver, command);
    }
    else {
        LOG_WARN_LCD("Write command function not implemented!");
        return 0;
    }
}

int sgfx_lcd_write_data8(const struct sgfx_lcd_driver ** driver, const uint8_t * src, size_t size)
{
    lcd_write_data8_fn_t fn = (*driver)->write_data8;

    if(fn) {
        LOG_TRACE_LCD("LCD write data8, addr = %p, size = %zu", (const void *)src, size);
        return fn(driver, src, size);
    }
    else {
        LOG_WARN_LCD("Write data8 function not implemented!");
        return 0;
    }
}

int sgfx_lcd_write_data16(const struct sgfx_lcd_driver ** driver, const uint16_t * src, size_t size)
{
    lcd_write_data16_fn_t fn = (*driver)->write_data16;

    if(fn) {
        LOG_TRACE_LCD("LCD write data16, addr = %p, size = %zu", (const void *)src, size);
        return fn(driver, src, size);
    }
    else {
        LOG_WARN_LCD("Write data16 function not implemented!");
        return 0;
    }
}

int sgfx_lcd_copy_data(const struct sgfx_lcd_driver ** driver, const void * src, size_t size)
{
    lcd_copy_data_fn_t fn = (*driver)->copy_data;

    if(fn) {
        LOG_TRACE_LCD("LCD copy data, addr = %p, size = %zu", (const void *)src, size);
        return fn(driver, src, size);
    }
    else {
        LOG_WARN_LCD("Copy data function not implemented!");
        return 0;
    }
}

void sgfx_lcd_delay_ms(const struct sgfx_lcd_driver ** driver, uint32_t nms)
{
    lcd_delay_ms_fn_t fn = (*driver)->delay_ms;

    if(fn) {
        LOG_TRACE_LCD("Delay %d ms", nms);
        return fn(driver, nms);
    }
    else {
        LOG_WARN_LCD("Delay ms function not implemented!");
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _lcd_fill_point(const struct sgfx_display_drawing ** drawing, 
                         uint16_t x, 
                         uint16_t y, 
                         uint32_t color)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;

    lcd_fill_point_fn_t fn = (*self->lcd_drawing)->fill_point;

    if(fn) {
        fn(self->lcd_drawing, x, y, color);
    }
    else {
        LOG_WARN_LCD("LCD fill point function not implemented!");
    }
}

static void _lcd_fill_rectangle(const struct sgfx_display_drawing ** drawing, 
                             uint16_t x, 
                             uint16_t y, 
                             uint16_t w, 
                             uint16_t h, 
                             uint32_t color)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;

    lcd_fill_rectangle_fn_t fn = (*self->lcd_drawing)->fill_rectangle;

    if(fn) {
        fn(self->lcd_drawing, x, y, w, h, color);
    }
    else {
        LOG_WARN_LCD("LCD fill rect function not implemented!");
    }
}


static void _lcd_flush(const struct sgfx_display_drawing ** drawing,
                    uint16_t x1, 
                    uint16_t y1, 
                    uint16_t x2, 
                    uint16_t y2, 
                    const void * src)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;

    lcd_flush_fn_t fn = (*self->lcd_drawing)->flush;

    if(fn) {
        fn(self->lcd_drawing, x1, y1, x2, y2, src);
    }
    else {
        LOG_WARN_LCD("LCD flush function not implemented!");
    }
}

static int _lcd_ioctrl(const struct sgfx_display_drawing ** drawing,
                    uint32_t command, 
                    void * arg)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;

    lcd_ioctrl_fn_t fn = (*self->lcd_drawing)->ioctrl;

    if(fn) {
        return fn(self->lcd_drawing, command, arg);
    }
    else {
        LOG_WARN_LCD("LCD ioctrl function not implemented!");
        return 0;
    }
}

static const struct sgfx_display_drawing tDisplayDrawingLCD = 
{
    .fill_point     = _lcd_fill_point,
    .fill_rectangle = _lcd_fill_rectangle,
    .flush          = _lcd_flush,
    .ioctrl         = _lcd_ioctrl,
};

void sgfx_lcd_register(struct sgfx_lcd * self, const struct sgfx_lcd_drawing ** drawing)
{
    self->display_drawing = &tDisplayDrawingLCD;
    self->lcd_drawing = drawing;

    LOG_INFO_LCD("LCD instance registered with drawing: %p", (const void *)drawing);
}


/******************************* (END OF FILE) *********************************/



 







