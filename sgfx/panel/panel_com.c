/**
 * @file panel_com.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "panel_com.h"
#include "display_log.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void panel_spi_select(const struct panel_spi ** self, int8_t select)
{    
    spi_select_fn_t fn = (*self)->select;
    
    if(fn) {
        fn(self, select);
    }
    else {
        LOG_WARN_DISPLAY("SPI select function not implemented!");
    }
}

int panel_spi_write_command(const struct panel_spi ** self, const uint8_t * command, size_t size)
{
    spi_write_command_fn_t fn = (*self)->write_command;
    
    if(fn) {
        return fn(self, command, size);
    }
    else {
        LOG_WARN_DISPLAY("SPI write command function not implemented!");
        return -1;
    }
}

int panel_spi_write_data8(const struct panel_spi ** self, const uint8_t * data, size_t size)
{
    spi_write_data8_fn_t fn = (*self)->write_data8;
    
    if(fn) {
        return fn(self, data, size);
    }
    else {
        LOG_WARN_DISPLAY("SPI write data8 function not implemented!");
        return -1;
    }
}

int panel_spi_write_data16(const struct panel_spi ** self, const uint16_t * data, size_t size)
{
    spi_write_data16_fn_t fn = (*self)->write_data16;
    
    if(fn) {
        return fn(self, data, size);
    }
    else {
        LOG_WARN_DISPLAY("SPI write data16 function not implemented!");
        return -1;
    }
}

int panel_spi_dma_transfer(const struct panel_spi ** self, const void * data, size_t size)
{
    spi_dma_transfer_fn_t fn = (*self)->dma_transfer;
    
    if(fn) {
        return fn(self, data, size);
    }
    else {
        LOG_WARN_DISPLAY("SPI DMA transfer function not implemented!");
        return -1;
    }
}

void panel_spi_delay_ms(const struct panel_spi ** self, uint32_t ms)
{
    spi_delay_ms_fn_t fn = (*self)->delay_ms;
    
    if(fn) {
        fn(ms);
    }
    else {
        LOG_WARN_DISPLAY("SPI delay function not implemented!");
    }
}

int panel_prgb_write_mem()
{

}

int panel_prgb_dma2d_fill_mem()
{

}

int panel_prgb_dma2d_transfer()
{

}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







