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
#include "sgfx_config.h"
/*********************
 *      MACROS
 *********************/


#if SGFX_LOG_COLOR_ENABLE
    #define SGFX_LOG_COLOR_RED     "\033[31m"
    #define SGFX_LOG_COLOR_GREEN   "\033[32m"
    #define SGFX_LOG_COLOR_YELLOW  "\033[33m"
    #define SGFX_LOG_COLOR_BLUE    "\033[34m"
    #define SGFX_LOG_COLOR_WHITE   "\033[37m"
    #define SGFX_LOG_COLOR_RESET   "\033[0m"
#else 
    #define SGFX_LOG_COLOR_RED     ""
    #define SGFX_LOG_COLOR_GREEN   ""
    #define SGFX_LOG_COLOR_YELLOW  ""
    #define SGFX_LOG_COLOR_BLUE    ""
    #define SGFX_LOG_COLOR_WHITE   ""
    #define SGFX_LOG_COLOR_RESET   ""
#endif /* SGFX_LOG_COLOR_ENABLE */

#if SGFX_LOG_ENABLE
    #define SGFX_LOG_WRITE(fmt, ...)  do{ SGFX_LOG_PRINTF(fmt, ##__VA_ARGS__); } while(0)

    #define SGFX_LOG_TRACE(fmt, ...)  SGFX_LOG_WRITE(SGFX_LOG_COLOR_GREEN"[Trace] [%s:%d] " \
                                                      fmt SGFX_LOG_COLOR_RESET"\r\n", \
                                                      __FUNCTION__, __LINE__, ##__VA_ARGS__)

    #define SGFX_LOG_INFO(fmt, ...)   SGFX_LOG_WRITE(SGFX_LOG_COLOR_BLUE"[Info ] [%s:%d] " \
                                                      fmt SGFX_LOG_COLOR_RESET"\r\n", \
                                                      __FUNCTION__, __LINE__, ##__VA_ARGS__)

    #define SGFX_LOG_WARN(fmt, ...)   SGFX_LOG_WRITE(SGFX_LOG_COLOR_YELLOW"[Warn ] [%s:%d] " \
                                                      fmt SGFX_LOG_COLOR_RESET"\r\n", \
                                                      __FUNCTION__, __LINE__, ##__VA_ARGS__)

    #define SGFX_LOG_ERROR(fmt, ...)  SGFX_LOG_WRITE(SGFX_LOG_COLOR_RED"[Error] [%s:%d] " \
                                                      fmt SGFX_LOG_COLOR_RESET"\r\n", \
                                                      __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
    #define SGFX_LOG_WRITE(fmt, ...)  do{} while(0)
    #define SGFX_LOG_TRACE(fmt, ...)  do{} while(0)
    #define SGFX_LOG_INFO(fmt, ...)   do{} while(0)
    #define SGFX_LOG_WARN(fmt, ...)   do{} while(0)
    #define SGFX_LOG_ERROR(fmt, ...)  do{} while(0)
#endif /* SGFX_LOG_ENABLE */

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


