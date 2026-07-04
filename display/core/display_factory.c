/**
 * @file display_factory.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/

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
#if 0
const struct display_painter ** 
display_get_painter_instance(display_panel_type_t panel)
{


    switch(panel) {

        case DISPLAY_PANEL_ST7735: 
        {



            

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
    #endif
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 









