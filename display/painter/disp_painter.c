/**
 * @file disp_painter.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "../display.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void disp_painter_fill_point(const struct display * self, 
                             uint16_t x, 
                             uint16_t y, 
                             uint32_t color)
{
    fill_point_fn_t fn = (*self->painter)->fill_point;
    
    if(fn)
        fn(self->painter, x, y, color);
}

void disp_painter_fill_rectangle(const struct display * self, 
                                 uint16_t x, 
                                 uint16_t y, 
                                 uint16_t w, 
                                 uint16_t h, 
                                 uint32_t color)
{
    fill_rectangle_fn_t fn = (*self->painter)->fill_rectangle;
    if(fn)
        fn(self->painter, x, y, w, h, color);
}

void disp_painter_flush(const struct display * self, 
                        uint16_t x1, 
                        uint16_t y1, 
                        uint16_t x2, 
                        uint16_t y2, 
                        const void * data)
{
    flush_fn_t fn = (*self->painter)->flush;
    
    if(fn)
        fn(self->painter, x1, y1, x2, y2, data);
}



/******************************* (END OF FILE) *********************************/



 







