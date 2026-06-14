/**
 * @file display_port_spi.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "display_port_spi.h"
#include "common/display_log.h"
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void spi_select(const struct panel_spi ** spi, int8_t cs)
{
    const struct display_port_spi * self = (const struct display_port_spi *)spi;

    (void)self;

    LOG_TRACE_DISPLAY("SPI select: %d", cs);
}

static int spi_write_command(const struct panel_spi ** self, const uint8_t * command, size_t size)
{
    const struct display_port_spi * self = (const struct display_port_spi *)self;

    (void)self;
    (void)size;

    LOG_TRACE_DISPLAY("SPI write command: 0x%02x", command[0]);

    return 0;
}

static int spi_write_data8(const struct panel_spi ** self, const uint8_t * data, size_t size)
{
    const struct display_port_spi * self = (const struct display_port_spi *)self;

    (void)self;
    (void)size;

    LOG_TRACE_DISPLAY("SPI write data8: 0x%02x", data[0]);
    
    return 0;
}

static int spi_write_data16(const struct panel_spi ** self, const uint16_t * data, size_t size)
{
    const struct display_port_spi * self = (const struct display_port_spi *)self;

    (void)self;
    (void)size;

    LOG_TRACE_DISPLAY("SPI write data16: 0x%04x", data[0]);

    return 0;
}

static int spi_dma_transfer(const struct panel_spi ** self, const void * data, size_t size)
{
    const struct display_port_spi * self = (const struct display_port_spi *)self;

    (void)self;
    (void)size;

    LOG_TRACE_DISPLAY("SPI DMA transfer: %zu bytes", size);

    return 0;
}


static const struct panel_spi spi = 
{
    .select = spi_select,
    .write_command = spi_write_command,
    .write_data8 = spi_write_data8,
    .write_data16 = spi_write_data16,
    .dma_transfer = spi_dma_transfer,
};


void display_port_spi_register(struct display_port_spi * self, void * platform_data)
{
    self->spi = &spi;
    self->platform_data = platform_data;
}


/******************************* (END OF FILE) *********************************/



 







