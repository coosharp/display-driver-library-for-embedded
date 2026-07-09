/**
 * @file sgfx_st7735.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_st7735.h"
/*********************
 *      MACROS
 *********************/

/**********************
 *      DEFINES
 **********************/ 


#define LOG_TRACE_ST7735
#define LOG_INFO_ST7735
#define LOG_WARN_ST7735
#define LOG_ERROR_ST7735

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static const uint8_t st7735_sleep_out_params[] = {0x00};
static const uint8_t st7735_frame_rate_ctrl1_params[] = {0x05, 0x3C, 0x3C};
static const uint8_t st7735_frame_rate_ctrl2_params[] = {0x05, 0x3C, 0x3C};
static const uint8_t st7735_frame_rate_ctrl3_params[] = {0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C};
static const uint8_t st7735_frame_inversion_ctrl_params[] = {0x03};
static const uint8_t st7735_pwr_ctrl1_params[] = {0x28, 0x08, 0x04};
static const uint8_t st7735_pwr_ctrl2_params[] = {0xC0};
static const uint8_t st7735_pwr_ctrl3_params[] = {0x0D, 0x00};
static const uint8_t st7735_pwr_ctrl4_params[] = {0x8D, 0x2A};
static const uint8_t st7735_pwr_ctrl5_params[] = {0x8D, 0xEE};
static const uint8_t st7735_vcomh_vcoml_ctrl1_params[] = {0x1A};
static const uint8_t st7735_color_mode_params[] = {ST7735_FORMAT_RBG444, ST7735_FORMAT_RBG565, ST7735_FORMAT_RBG666};
static const uint8_t st7735_pv_gamma_ctrl_params[] = {0x04, 0x22, 0x07, 0x0A, 0x2E, 0x30, 0x25, 0x2A, 0x28, 0x26, 0x2E, 0x3A, 0x00, 0x01, 0x03, 0x13};
static const uint8_t st7735_nv_gamma_ctrl_params[] = {0x04, 0x16, 0x06, 0x0D, 0x2D, 0x26, 0x23, 0x27, 0x27, 0x25, 0x2D, 0x3B, 0x01, 0x00, 0x04, 0x13};
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void sgfx_st7735_prepare()
{

}

void sgfx_st7735_fill_point()
{

}

void sgfx_st7735_fill_rectangle()
{

}

void sgfx_st7735_flush()
{

}


/**********************
 *   STATIC FUNCTIONS
 **********************/
static void _st7735_write_reg()
{

}

static void _st7735_set_cursor()
{

}

static void _st7735_set_window()
{

}

static void _st7735_set_orientation()
{

}


/******************************* (END OF FILE) *********************************/



 







