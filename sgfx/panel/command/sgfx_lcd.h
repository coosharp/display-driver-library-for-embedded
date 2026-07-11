/**
 * @file sgfx_lcd.h
 *
 */
  
#ifndef _SGFX_LCD_H
#define _SGFX_LCD_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "sgfx_display.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
typedef struct sgfx_lcd_drawing sgfx_lcd_drawing_t;


typedef void (* lcd_fill_point_fn_t)    (const sgfx_lcd_drawing_t ** drawing, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint32_t color);
typedef void (* lcd_fill_rectangle_fn_t)(const sgfx_lcd_drawing_t ** drawing, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint16_t w, 
                                     uint16_t h, 
                                     uint32_t color);
typedef void (* lcd_flush_fn_t)         (const sgfx_lcd_drawing_t ** drawing, 
                                     uint16_t x1, 
                                     uint16_t y1, 
                                     uint16_t x2, 
                                     uint16_t y2, 
                                     const void * data);
typedef int  (* lcd_ioctrl_fn_t)        (const sgfx_lcd_drawing_t ** drawing, 
                                     uint32_t command, 
                                     void * arg);

typedef struct sgfx_lcd_driver sgfx_lcd_driver_t;

typedef int (* lcd_start_transfer_fn_t) (const sgfx_lcd_driver_t ** driver);
typedef int (* lcd_stop_transfer_fn_t) (const sgfx_lcd_driver_t ** driver);
typedef int (* lcd_write_command_fn_t)(const sgfx_lcd_driver_t ** driver, uint8_t command);
typedef int (* lcd_write_data8_fn_t)(const sgfx_lcd_driver_t ** driver, const uint8_t * src, size_t size);
typedef int (* lcd_write_data16_fn_t)(const sgfx_lcd_driver_t ** driver, const uint16_t * src, size_t size);
typedef int (* lcd_copy_data_fn_t)(const sgfx_lcd_driver_t ** driver, const void * src, size_t size);
typedef int (* lcd_delay_ms_fn_t) (const sgfx_lcd_driver_t ** driver, uint32_t ms);

struct sgfx_lcd_drawing
{
    lcd_fill_point_fn_t    fill_point;
    lcd_fill_rectangle_fn_t fill_rectangle;
    lcd_flush_fn_t         flush;
    lcd_ioctrl_fn_t        ioctrl;
};

struct sgfx_lcd_driver
{
    lcd_write_command_fn_t write_command;
    lcd_write_data8_fn_t write_data8;
    lcd_write_data16_fn_t write_data16;
    lcd_copy_data_fn_t copy_data;
    lcd_delay_ms_fn_t delay_ms;
};

struct sgfx_lcd
{
    const struct sgfx_display_drawing * drawing_ops;
    const struct sgfx_lcd_drawing ** drawing_impl;
    const struct sgfx_lcd_driver ** driver;
}
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void sgfx_lcd_fill_point(const struct sgfx_display_drawing ** drawing, 
                         uint16_t x, 
                         uint16_t y, 
                         uint32_t color);

void sgfx_lcd_fill_rectangle(const struct sgfx_display_drawing ** drawing, 
                             uint16_t x, 
                             uint16_t y, 
                             uint16_t w, 
                             uint16_t h, 
                             uint32_t color);
                            
void sgfx_lcd_flush(const struct sgfx_display_drawing ** drawing,
                    uint16_t x1, 
                    uint16_t y1, 
                    uint16_t x2, 
                    uint16_t y2, 
                    const void * data);

int sgfx_lcd_ioctrl(const struct sgfx_display_drawing ** drawing,
                    uint32_t command, 
                    void * arg);
 


int sgfx_lcd_start_transfer(const struct sgfx_lcd_driver ** driver);
int sgfx_lcd_stop_transfer(const struct sgfx_lcd_driver ** driver);
int sgfx_lcd_write_command(const struct sgfx_lcd_driver ** driver, uint8_t command);
int sgfx_lcd_write_data8(const struct sgfx_lcd_driver ** driver, const uint8_t * src, size_t size);
int sgfx_lcd_write_data16(const struct sgfx_lcd_driver ** driver, const uint16_t * src, size_t size);
int sgfx_lcd_copy_data(const struct sgfx_lcd_driver ** driver, const void * src, size_t size);
void sgfx_lcd_delay_ms(const struct sgfx_lcd_driver ** driver);





#ifdef __cplusplus
}
#endif

#endif /*_SGFX_LCD_H*/


/******************************* (END OF FILE) *********************************/


