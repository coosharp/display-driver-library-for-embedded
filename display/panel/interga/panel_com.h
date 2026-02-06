/**
 * @file panel_com.h
 *
 */
  
#ifndef _PANEL_COM_H
#define _PANEL_COM_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/
typedef struct panel_spi panel_spi_t;
typedef void (* spi_select_fn_t)(const panel_spi_t ** self, int8_t select);
typedef int (* spi_write_command_fn_t)(const panel_spi_t ** self, const uint8_t * command, size_t size);
typedef int (* spi_write_data8_fn_t)(const panel_spi_t ** self, const uint8_t * data, size_t size);
typedef int (* spi_write_data16_fn_t)(const panel_spi_t ** self, const uint16_t * data, size_t size);
typedef int (* spi_dma_transfer_fn_t)(const panel_spi_t ** self, const void * data, size_t size);

struct panel_spi
{
    spi_select_fn_t select;
    spi_write_command_fn_t write_command;
    spi_write_data8_fn_t write_data8;
    spi_write_data16_fn_t write_data16;
    spi_dma_transfer_fn_t dma_transfer;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void panel_spi_select(const panel_spi_t ** self, int8_t select);
int panel_spi_write_command(const panel_spi_t ** self, const uint8_t * command, size_t size);
int panel_spi_write_data8(const panel_spi_t ** self, const uint8_t * data, size_t size);
int panel_spi_write_data16(const panel_spi_t ** self, const uint16_t * data, size_t size);
int panel_spi_dma_transfer(const panel_spi_t ** self, const void * data, size_t size);

 

#ifdef __cplusplus
}
#endif

#endif /*_PANEL_COM_H*/


/******************************* (END OF FILE) *********************************/





