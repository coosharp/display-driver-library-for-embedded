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
typedef void (* spi_delay_ms_fn_t)(uint32_t ms);

struct panel_spi
{
    spi_select_fn_t select;
    spi_write_command_fn_t write_command;
    spi_write_data8_fn_t write_data8;
    spi_write_data16_fn_t write_data16;
    spi_dma_transfer_fn_t dma_transfer;
    spi_delay_ms_fn_t delay_ms;
};


typedef struct panel_prgb panel_prgb_t;


struct panel_rgb
{

};


/**********************
*  GLOBAL PROTOTYPES
 **********************/
void panel_spi_select(const struct panel_spi ** self, int8_t select);
int panel_spi_write_command(const struct panel_spi ** self, const uint8_t * command, size_t size);
int panel_spi_write_data8(const struct panel_spi ** self, const uint8_t * data, size_t size);
int panel_spi_write_data16(const struct panel_spi ** self, const uint16_t * data, size_t size);
int panel_spi_dma_transfer(const struct panel_spi ** self, const void * data, size_t size);
void panel_spi_delay_ms(const struct panel_spi ** self, uint32_t ms);
 


#ifdef __cplusplus
}
#endif

#endif /*_PANEL_COM_H*/


/******************************* (END OF FILE) *********************************/





