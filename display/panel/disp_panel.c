/**
 * @file disp_panel.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "disp_panel.h"
#include "../display.h"
#include "./interga/panel_st7735.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void disp_panel_register_instance(struct display * self, disp_panel_type_t type)
{
    static struct st7735 st7735_instance;

    switch(type) {
        case DISP_PANEL_ST7735:
            const panel_spi_t ** spi = disp_port_get_spi_instance();
            st7735_register(&st7735_instance, spi);
            self->painter = &st7735_instance.painter;
            break;
        default:
            break;
    }
}




/******************************* (END OF FILE) *********************************/



 







