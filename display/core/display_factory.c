/**
 * @file display_factory.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "display_factory.h"
#include "display.h"
#include "panel/panel_st7735.h"
#include "panel/panel_com.h"
#include "backlight/backlight.h"
#include "backlight/backlight_ctrl.h"

#include "porting/display_port_spi.h"
#include "porting/display_port_backlight.h"
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
const struct display_painter ** 
display_get_painter_instance(display_panel_type_t panel)
{


    switch(panel) {

        case DISPLAY_PANEL_ST7735: 
        {
            static struct st7735 st7735_instance;
            static struct panel_spi st7735_spi_instance;


            st7735_register(&st7735_instance, &st7735_spi_instance);

            return &st7735_instance.painter;
        }
        break;
            
        default:
            return NULL;
    }
}

const struct display_backlight **
display_get_backlight_instance(void)
{
    static struct backlight backlight_instance;
    static struct backlight_ctrl backlight_ctrl_instance;

    return &backlight_instance.backlight;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 









