/**
 * @file panel_st7735.h
 *
 */
  
#ifndef _PANEL_ST7735_H
#define _PANEL_ST7735_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>
#include "display.h"
#include "panel_com.h"
/**********************
 *      DEFINES
 **********************/

/*********************
 *    DECLARATIONS
 *********************/
struct st7735_context
{
    uint32_t height;
    uint32_t width;
    uint16_t  rotation;
    char color_mode[7];
};

struct st7735
{
    const struct display_painter * painter;
    const struct panel_spi ** spi;
    struct st7735_context context;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void st7735_register(struct st7735 * self, 
                     const struct panel_spi ** spi,
                     const struct st7735_context * context);
/**********************
 *      MACROS
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_PANEL_ST7735_H*/


/******************************* (END OF FILE) *********************************/


