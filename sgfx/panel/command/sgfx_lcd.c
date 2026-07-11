/**
 * @file sgfx_lcd.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_lcd.h"

/*********************
 *      MACROS
 *********************/

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static const struct sgfx_display_drawing lcd_drawing = 
{
    .fill_point = sgfx_lcd_fill_point,
    .fill_rectangle = sgfx_lcd_fill_rectangle,
    .flush = sgfx_lcd_flush,
    .ioctrl = sgfx_lcd_ioctrl,
};
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

void sgfx_lcd_fill_point(const struct sgfx_display_drawing ** drawing, 
                         uint16_t x, 
                         uint16_t y, 
                         uint32_t color)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;
}

void sgfx_lcd_fill_rectangle(const struct sgfx_display_drawing ** drawing, 
                             uint16_t x, 
                             uint16_t y, 
                             uint16_t w, 
                             uint16_t h, 
                             uint32_t color)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;
}


void sgfx_lcd_flush(const struct sgfx_display_drawing ** drawing,
                    uint16_t x1, 
                    uint16_t y1, 
                    uint16_t x2, 
                    uint16_t y2, 
                    const void * data)
{

}

int sgfx_lcd_ioctrl(const struct sgfx_display_drawing ** drawing,
                    uint32_t command, 
                    void * arg)
{
    const struct sgfx_lcd * self = (const struct sgfx_lcd *)drawing;
}

int sgfx_lcd_start_transfer(const struct sgfx_lcd_driver ** driver)
{
    lcd_start_transfer_fn_t fn = (*self->driver)->start_transfer;

}

int sgfx_lcd_stop_transfer(const struct sgfx_lcd_driver ** driver)
{
    lcd_stop_transfer_fn_t fn = (*self->driver)->stop_transfer;
}

int sgfx_lcd_write_command(const struct sgfx_lcd_driver ** driver, uint8_t command)
{
    lcd_write_command_fn_t fn = (*self->driver)->write_command;
}

int sgfx_lcd_write_data8(const struct sgfx_lcd_driver ** driver, const uint8_t * src, size_t size)
{
    lcd_write_data8_fn_t fn = (*self->driver)->write_data8;
}

int sgfx_lcd_write_data16(const struct sgfx_lcd_driver ** driver, const uint16_t * src, size_t size)
{
    lcd_write_data16_fn_t fn = (*self->driver)->write_data16;
}

int sgfx_lcd_copy_data(const struct sgfx_lcd_driver ** driver, const void * src, size_t size)
{
    lcd_copy_data_fn_t fn = (*self->driver)->copy_data;
}

void sgfx_lcd_delay_ms(const struct sgfx_lcd_driver ** driver)
{
    lcd_delay_ms_fn_t fn = (*self->driver)->delay_ms;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







