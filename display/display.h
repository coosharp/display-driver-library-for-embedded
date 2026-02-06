/**
 * @file display.h
 *
 */
  
#ifndef _DISPLAY_H
#define _DISPLAY_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>

#include "./painter/disp_painter.h"
#include "./backlight/disp_backlight.h"
#include "./panel/disp_panel.h"
#include "./panel/interga/panel_com.h"
/*********************
 *    DECLARATIONS
 *********************/
struct display
{
    const struct disp_painter ** painter;
    const struct disp_backlight ** backlight;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/

/* defined in disp_painter.c */
void disp_painter_fill_point    (const struct display * self, 
                                 uint16_t x, 
                                 uint16_t y, 
                                 uint32_t color);
void disp_painter_fill_rectangle(const struct display * self, 
                                 uint16_t x, 
                                 uint16_t y, 
                                 uint16_t w, 
                                 uint16_t h, 
                                 uint32_t color);
void disp_painter_flush         (const struct display * self, 
                                 uint16_t x1, 
                                 uint16_t y1, 
                                 uint16_t x2, 
                                 uint16_t y2, 
                                 const void * data);


/* defined in disp_backlight.c */
void disp_backlight_register_instance(struct display * self, const struct disp_backlight ** backlight);
void disp_backlight_turn_on          (const struct display * self);
void disp_backlight_turn_off         (const struct display * self);
void disp_backlight_set_brightness   (const struct display * self, uint8_t brightness);

/* defined in disp_panel.c */
void disp_panel_register_instance(struct display * self, disp_panel_type_t type);

/* defined in panel_com.c */
const panel_spi_t ** disp_port_get_spi_instance(void);

/* defined in disp_backlight_port.c */
const disp_backlight_t ** disp_port_get_backlight_instance(void);



#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_H*/


/******************************* (END OF FILE) *********************************/


