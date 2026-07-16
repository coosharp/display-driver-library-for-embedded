/**
 * @file sgfx_spi.h
 *
 */
  
#ifndef _SGFX_SPI_H
#define _SGFX_SPI_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>
/*********************
 *      MACROS
 *********************/

/*********************
 *    DECLARATIONS
 *********************/

typedef int     (* spi_chip_select_enable)  (void);
typedef int     (* spi_chip_select_disable) (void);
typedef int     (* spi_write_command)       (uint8_t command);
typedef int     (* spi_write_data8)         (const uint8_t * src, size_t size);
typedef int     (* spi_dma_transfer)        (const void * src, size_t size);
typedef void    (* spi_delay_ms)            (uint32_t ms);

struct sgfx_spi
{
    const struct sgfx_lcd_driver * driver;

    spi_chip_select_enable  chip_select_enable;
    spi_chip_select_disable chip_select_disable;
    spi_write_command       write_command;
    spi_write_data8         write_data8;
    spi_dma_transfer        dma_transfer;
    spi_delay_ms            delay_ms;

    void * user_data;
};
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void sgfx_spi_register(struct sgfx_spi * self);


#ifdef __cplusplus
}
#endif

#endif /*_SGFX_SPI_H*/


/******************************* (END OF FILE) *********************************/


