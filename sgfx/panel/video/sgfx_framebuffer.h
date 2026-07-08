/**
 * @file panel_framebuffer.h
 *
 */
  
#ifndef _PANEL_FRAMEBUFFER_H
#define _PANEL_FRAMEBUFFER_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "display.h"
#include "panel_com.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct framebuffer 
{  
    const struct display_painter * painter;
    const struct panel_prgb ** prgb;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/



#ifdef __cplusplus
}
#endif

#endif /*_PANEL_FRAMEBUFFER_H*/


/******************************* (END OF FILE) *********************************/


