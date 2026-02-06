/**
 * @file disp_painter.h
 *
 */
  
#ifndef _DISP_PAINTER_H
#define _DISP_PAINTER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *    DECLARATIONS
 *********************/
typedef struct disp_painter disp_painter_t;
typedef void (* fill_point_fn_t)    (const disp_painter_t ** self, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint32_t color);
typedef void (* fill_rectangle_fn_t)(const disp_painter_t ** self, 
                                     uint16_t x, 
                                     uint16_t y, 
                                     uint16_t w, 
                                     uint16_t h, 
                                     uint32_t color);
typedef void (* flush_fn_t)         (const disp_painter_t ** self, 
                                     uint16_t x1, 
                                     uint16_t y1, 
                                     uint16_t x2, 
                                     uint16_t y2, 
                                     const void * data);


struct disp_painter
{
    fill_point_fn_t fill_point;
    fill_rectangle_fn_t fill_rectangle;
    flush_fn_t flush;
};


 

#ifdef __cplusplus
}
#endif

#endif /*_DISP_PAINTER_H*/


/******************************* (END OF FILE) *********************************/


