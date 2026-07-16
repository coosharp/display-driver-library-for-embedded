/**
 * @file sgfx_spi.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_spi.h"
#include "sgfx_lcd.h"
#include "sgfx_log.h"
/*********************
 *      MACROS
 *********************/
#if SGFX_LOG_SPI_ENABLE
    #define LOG_TRACE_SPI   SGFX_LOG_TRACE
    #define LOG_INFO_SPI    SGFX_LOG_INFO
    #define LOG_WARN_SPI    SGFX_LOG_WARN
    #define LOG_ERROR_SPI   SGFX_LOG_ERROR
#else 
    #define LOG_TRACE_SPI
    #define LOG_INFO_SPI
    #define LOG_WARN_SPI
    #define LOG_ERROR_SPI
#endif


/**********************
 *      FUNCTIONS
 **********************/

static int _spi_chip_select_enable(const struct sgfx_lcd_driver ** driver)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    spi_chip_select_enable fn = self->chip_select_enable;

    LOG_TRACE_SPI("SPI CS enable!");

    if(fn) {
        return fn();
    }
    else {

    }
}
 
static int _spi_chip_select_disable(const struct sgfx_lcd_driver ** driver)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    LOG_TRACE_SPI("SPI CS disable!");

    return 0;
}

static int _spi_write_command(const struct sgfx_lcd_driver ** driver, uint8_t command)
{
    LOG_INFO_SPI("");

    return 0;
}

static int _spi_write_data8(const struct sgfx_lcd_driver ** driver, const uint8_t * src, size_t size)
{
    LOG_INFO_SPI("");

    return 0;
}

static int _spi_dma_transfer(const struct sgfx_lcd_driver ** driver, const void * src, size_t size)
{
    LOG_INFO_SPI("");

    return 0;
}

static void _spi_delay_ms(const struct sgfx_lcd_driver ** driver, uint32_t ms)
{
    LOG_INFO_SPI("");
}


static const struct sgfx_lcd_driver tSpiDriver = 
{
    .start_transfer = _spi_chip_select_enable,
    .stop_transfer  = _spi_chip_select_disable,
    .write_command  = _spi_write_command,
    .write_data8    = _spi_write_data8,
    .copy_data      = _spi_dma_transfer,
    .delay_ms       = _spi_delay_ms,
};

void sgfx_spi_register(struct sgfx_spi * self)
{
    self->driver = &tSpiDriver;

    LOG_INFO_SPI("driver init");
}

/******************************* (END OF FILE) *********************************/



 







