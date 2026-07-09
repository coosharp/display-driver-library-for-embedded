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


struct sgfx_lcd_drawing
{
    lcd_fill_point_fn_t    fill_point;
    lcd_fill_rectangle_fn_t fill_rectangle;
    lcd_flush_fn_t         flush;
    lcd_ioctrl_fn_t        ioctrl;
};

struct sgfx_lcd_interface
{

};

struct sgfx_lcd
{
    const struct sgfx_display_drawing * drawing_ops;
    const struct sgfx_lcd_drawing ** drawing_impl;
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
 

#ifdef __cplusplus
}
#endif

#endif /*_SGFX_LCD_H*/


/******************************* (END OF FILE) *********************************/


