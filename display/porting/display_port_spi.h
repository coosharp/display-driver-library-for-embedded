/**
 * @file display_port_spi.h
 *
 */
  
#ifndef _DISPLAY_PORT_SPI_H
#define _DISPLAY_PORT_SPI_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "panel/panel_com.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct display_port_spi
{
    const struct panel_spi * spi;
    void * platform_data;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void display_port_spi_register(struct display_port_spi * self, void * platform_data);
 

#ifdef __cplusplus
}
#endif

#endif /*_DISPLAY_PORT_SPI_H*/


/******************************* (END OF FILE) *********************************/


