/**
 * @file display_log.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "display_log.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *      DEFINES
 **********************/ 
#if DISPLAY_LOG_ENABLE_COLOR
    #define DISPLAY_LOG_COLOR_RED     "\033[31m"
    #define DISPLAY_LOG_COLOR_GREEN   "\033[32m"
    #define DISPLAY_LOG_COLOR_YELLOW  "\033[33m"
    #define DISPLAY_LOG_COLOR_BLUE    "\033[34m"
    #define DISPLAY_LOG_COLOR_WHITE   "\033[37m"
    #define DISPLAY_LOG_COLOR_RESET   "\033[0m"
#else 
    #define DISPLAY_LOG_COLOR_RED     ""
    #define DISPLAY_LOG_COLOR_GREEN   ""
    #define DISPLAY_LOG_COLOR_YELLOW  ""
    #define DISPLAY_LOG_COLOR_BLUE    ""
    #define DISPLAY_LOG_COLOR_WHITE   ""
    #define DISPLAY_LOG_COLOR_RESET   ""
#endif /* DISPLAY_LOG_ENABLE_COLOR */
/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void display_log_printf()
{
    
}
/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







