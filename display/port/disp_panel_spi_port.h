/**
 * @file disp_panel_spi_port.h
 *
 */
  
#ifndef _DISP_PANEL_SPI_PORT_H
#define _DISP_PANEL_SPI_PORT_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "../panel/interga/panel_com.h"
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
struct port_spi
{
    const struct panel_spi * ops;
    void * platform_data;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/

 

#ifdef __cplusplus
}
#endif

#endif /*_DISP_PANEL_SPI_PORT_H*/


/******************************* (END OF FILE) *********************************/


