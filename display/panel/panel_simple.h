/**
 * @file panel_simple.h
 *
 */
  
#ifndef _PANEL_SIMPLE_H
#define _PANEL_SIMPLE_H

#if 0
#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../painter/disp_painter.h"
#include "panel_com.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct simple_panel 
{
    const struct disp_painter * painter;
    const struct panel_prgb ** prgb;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/

 #endif

#ifdef __cplusplus
}
#endif

#endif /*_PANEL_SIMPLE_H*/


/******************************* (END OF FILE) *********************************/


