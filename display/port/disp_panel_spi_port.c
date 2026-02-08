/**
 * @file disp_panel_spi_port.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "./disp_panel_spi_port.h"
/**********************
 *   STATIC FUNCTIONS
 **********************/
static void spi_select(const struct panel_spi ** self, int8_t cs)
{
    (void)self;
    printf("spi_select: %d\n", cs);
}

static int spi_write_command(const struct panel_spi ** self, const uint8_t * command, size_t size)
{
    (void)self;
    (void)size;
    printf("spi_write_command: 0x%02x\n", command[0]);
    return 0;
}

static int spi_write_data8(const struct panel_spi ** self, const uint8_t * data, size_t size)
{
    (void)self;
    (void)size;
    printf("spi_write_data8: 0x%02x\n", data[0]);
    return 0;
}

static int spi_write_data16(const struct panel_spi ** self, const uint16_t * data, size_t size)
{
    (void)self;
    (void)size;
    printf("spi_write_data16: 0x%04x\n", data[0]);
    return 0;
}

static int spi_dma_transfer(const struct panel_spi ** self, const void * data, size_t size)
{
    (void)self;
    (void)size;
    printf("spi_dma_transfer: %p\n", data);
    return 0;
}


static const struct panel_spi spi_ops = 
{
    .select = spi_select,
    .write_command = spi_write_command,
    .write_data8 = spi_write_data8,
    .write_data16 = spi_write_data16,
    .dma_transfer = spi_dma_transfer,
};


void disp_port_get_spi_instance(struct port_spi * spi, void * platform_data)
{
    spi->ops = &spi_ops;
    spi->platform_data = platform_data;
}


/******************************* (END OF FILE) *********************************/



 







