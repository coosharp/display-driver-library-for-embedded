/**
 * @file display_port_backlight.h
 *
 */
  
#ifndef _DISPLAY_PORT_BACKLIGHT_H
#define _DISPLAY_PORT_BACKLIGHT_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "backlight/backlight_ctrl.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct display_port_backlight 
{
   const struct backlight_ctrl * ctrl;
   void * platform_data;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void display_port_backlight_register(struct display_port_backlight * self, void * platform_data);
 

#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_PORT_BACKLIGHT_H*/


/******************************* (END OF FILE) *********************************/


