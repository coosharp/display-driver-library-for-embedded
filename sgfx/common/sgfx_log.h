/**
 * @file display_log.h
 *
 */
  
#ifndef _DISPLAY_LOG_H
#define _DISPLAY_LOG_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "display_config.h"
/*********************
 *      MACROS
 *********************/
z

#if LOG_ENABLE_DISPLAY_COLOR
    #define LOG_COLOR_RED     "\033[31m"
    #define LOG_COLOR_GREEN   "\033[32m"
    #define LOG_COLOR_YELLOW  "\033[33m"
    #define LOG_COLOR_BLUE    "\033[34m"
    #define LOG_COLOR_WHITE   "\033[37m"
    #define LOG_COLOR_RESET   "\033[0m"
#else 
    #define LOG_COLOR_RED     ""
    #define LOG_COLOR_GREEN   ""
    #define LOG_COLOR_YELLOW  ""
    #define LOG_COLOR_BLUE    ""
    #define LOG_COLOR_WHITE   ""
    #define LOG_COLOR_RESET   ""
#endif /* LOG_ENABLE_DISPLAY_COLOR */

#if LOG_ENABLE_DISPLAY
    #define LOG_PRINTF_DISPLAY(fmt, ...)  do{ printf(fmt, ##__VA_ARGS__); } while(0)
    #define LOG_TRACE_DISPLAY(fmt, ...)  LOG_PRINTF_DISPLAY(LOG_COLOR_GREEN"[Trace] [%s:%d] " fmt LOG_COLOR_RESET"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_INFO_DISPLAY(fmt, ...)   LOG_PRINTF_DISPLAY(LOG_COLOR_BLUE"[Info ] [%s:%d] " fmt LOG_COLOR_RESET"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_WARN_DISPLAY(fmt, ...)   LOG_PRINTF_DISPLAY(LOG_COLOR_YELLOW"[Warn ] [%s:%d] " fmt LOG_COLOR_RESET"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_ERROR_DISPLAY(fmt, ...)  LOG_PRINTF_DISPLAY(LOG_COLOR_RED"[Error] [%s:%d] " fmt LOG_COLOR_RESET"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG_PRINTF_DISPLAY(fmt, ...)  do{} while(0)
    #define LOG_TRACE_DISPLAY(fmt, ...)  do{} while(0)
    #define LOG_INFO_DISPLAY(fmt, ...)   do{} while(0)
    #define LOG_WARN_DISPLAY(fmt, ...)   do{} while(0)
    #define LOG_ERROR_DISPLAY(fmt, ...)  do{} while(0)
#endif /* LOG_ENABLE_DISPLAY */

/*********************
 *    DECLARATIONS
 *********************/

/**********************
*  GLOBAL PROTOTYPES
 **********************/

 

#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_LOG_H*/


/******************************* (END OF FILE) *********************************/


