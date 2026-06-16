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
/*********************
 *      MACROS
 *********************/
#define LOG_ENABLE_DISPLAY  (1)

#if LOG_ENABLE_DISPLAY
    #define LOG_PRINTF_DISPLAY(fmt, ...)  do{ printf(fmt, ##__VA_ARGS__); } while(0)
    #define LOG_TRACE_DISPLAY(fmt, ...)  LOG_PRINTF_DISPLAY("[Trace] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_INFO_DISPLAY(fmt, ...)   LOG_PRINTF_DISPLAY("[Info ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_WARN_DISPLAY(fmt, ...)   LOG_PRINTF_DISPLAY("[Warn ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_ERROR_DISPLAY(fmt, ...)  LOG_PRINTF_DISPLAY("[Error] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
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


