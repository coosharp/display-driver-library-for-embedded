/**
 * @file panel_com.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "./panel_com.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void panel_spi_select(const panel_spi_t ** self, int8_t select)
{    
    spi_select_fn_t fn = (*self)->select;
    
    if(fn)
        fn(self, select);
}

int panel_spi_write_command(const panel_spi_t ** self, const uint8_t * command, size_t size)
{
    spi_write_command_fn_t fn = (*self)->write_command;
    
    if(fn)
        return fn(self, command, size);
    else 
        return -1;
}

int panel_spi_write_data8(const panel_spi_t ** self, const uint8_t * data, size_t size)
{
    spi_write_data8_fn_t fn = (*self)->write_data8;
    
    if(fn)
        return fn(self, data, size);
    else 
        return -1;
}

int panel_spi_write_data16(const panel_spi_t ** self, const uint16_t * data, size_t size)
{
    spi_write_data16_fn_t fn = (*self)->write_data16;
    
    if(fn)
        return fn(self, data, size);
    else 
        return -1;
}

int panel_spi_dma_transfer(const panel_spi_t ** self, const void * data, size_t size)
{
    spi_dma_transfer_fn_t fn = (*self)->dma_transfer;
    
    if(fn)
        return fn(self, data, size);
    else 
        return -1;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 







