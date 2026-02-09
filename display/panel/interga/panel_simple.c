/**
 * @file panel_simple.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "panel_simple.h"
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

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void simple_panel_register(struct simple_panel * self, const struct panel_prgb ** prgb)
{
    self->prgb = prgb;
}

void simple_panel_config_frame_buffer()
{
    
}

void simple_panel_prepare(const struct disp_painter ** painter)
{

}

void simple_panel_fill_point(const struct disp_painter ** painter, 
                             uint16_t x, 
                             uint16_t y, 
                             uint32_t color)
{

}

void simple_panel_fill_rectangle(const struct disp_painter ** painter, 
                                 uint16_t x, 
                                 uint16_t y, 
                                 uint16_t w, 
                                 uint16_t h, 
                                 uint32_t color)
{

}

void simple_panel_flush(const struct disp_painter ** painter,
                        uint16_t x1,
                        uint16_t y1,
                        uint16_t x2,
                        uint16_t y2,
                        const void * data)
{

}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







