/**
 * @file display_conf.h
 *
 */
  
#ifndef _DISPLAY_CONF_H
#define _DISPLAY_CONF_H


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

#define DISP_ASSERT_ENABLE 1
#define DISP_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)


#define DISP_UNUSED(_x_) (void)(_x_)

#if DISP_ASSERT_ENABLE
    #define DISP_ASSERT(_expr_, msg) do {                                                                       \
                                            if (!(_expr_)) {                                                    \
                                                DISP_LOG("[ASSERT] [%s:%d] %s\r\n", __FILE__, __LINE__, msg);   \
                                                while(1);                                                       \
                                            }                                                                   \
                                        } while(0)
#else
    #define DISP_ASSERT(_expr_, msg) do { } while(0)
#endif




#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_CONF_H*/


/******************************* (END OF FILE) *********************************/


