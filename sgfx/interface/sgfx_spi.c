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
    #define LOG_TRACE_SPI(fmt, ...)   SGFX_LOG_TRACE(fmt, ##__VA_ARGS__)
    #define LOG_INFO_SPI(fmt, ...)    SGFX_LOG_INFO(fmt, ##__VA_ARGS__)
    #define LOG_WARN_SPI(fmt, ...)    SGFX_LOG_WARN(fmt, ##__VA_ARGS__)
    #define LOG_ERROR_SPI(fmt, ...)   SGFX_LOG_ERROR(fmt, ##__VA_ARGS__)
#else 
    #define LOG_TRACE_SPI(fmt, ...)   do{} while(0)
    #define LOG_INFO_SPI(fmt, ...)    do{} while(0)
    #define LOG_WARN_SPI(fmt, ...)    do{} while(0)
    #define LOG_ERROR_SPI(fmt, ...)   do{} while(0)
#endif


/**********************
 *      FUNCTIONS
 **********************/

static int _spi_chip_select_enable(const struct sgfx_lcd_driver ** driver)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    spi_chip_select_enable fn = self->chip_select_enable;

    if(fn) {
        LOG_TRACE_SPI("SPI CS enable!");
        return fn();
    }
    else {
        LOG_WARN_SPI("SPI CS enable function not implemented!");
        return 0;
    }
}
 
static int _spi_chip_select_disable(const struct sgfx_lcd_driver ** driver)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    spi_chip_select_disable fn = self->chip_select_disable;

    if(fn) {
        LOG_TRACE_SPI("SPI CS disable!");
        return fn();
    }
    else {
        LOG_WARN_SPI("SPI CS disable function not implemented!");
        return 0;
    }
}

static int _spi_write_command(const struct sgfx_lcd_driver ** driver, uint8_t command)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    spi_write_command fn = self->write_command;

    if(fn) {
        LOG_TRACE_SPI("SPI write command: 0x%02x", command);
        return fn(command);
    }
    else {
        LOG_WARN_SPI("SPI write command function not implemented!");
        return 0;
    }
}

static int _spi_write_data8(const struct sgfx_lcd_driver ** driver, const uint8_t * src, size_t size)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver; 

    spi_write_data8 fn = self->write_data8;

    if(fn) {
        LOG_TRACE_SPI("SPI write data, addr = %p, size = %zu", (const void *)src, size);
        return fn(src, size);
    }
    else {
        LOG_WARN_SPI("SPI write data8 function not implemented!");
        return 0;
    }
}

static int _spi_dma_transfer(const struct sgfx_lcd_driver ** driver, const void * src, size_t size)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    spi_dma_transfer fn = self->dma_transfer;

    if(fn) {
        LOG_TRACE_SPI("SPI dma transfer data, addr = %p, size = %zu", (const void *)src, size);
        return fn(src, size);
    }
    else {
        LOG_WARN_SPI("SPI dma transfer function not implemented!");
        return 0;
    }
}

static void _spi_delay_ms(const struct sgfx_lcd_driver ** driver, uint32_t nms)
{
    const struct sgfx_spi * self = (const struct sgfx_spi *)driver;

    spi_delay_ms fn = self->delay_ms;

    if(fn) {
        LOG_TRACE_SPI("Delay %d ms", nms);
        fn(nms);
    }
    else {
        LOG_WARN_SPI("SPI delay ms function not implemented!");
    }
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

    LOG_INFO_SPI("SPI instance register");
}

/******************************* (END OF FILE) *********************************/



 







