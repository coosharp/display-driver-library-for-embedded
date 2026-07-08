/**
 * @file panel_st7735.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "panel_st7735.h"
/*********************
 *      MACROS
 *********************/
#define ST7735_NOP                          0x00U  /* No Operation: NOP                           */
#define ST7735_SW_RESET                     0x01U  /* Software reset: SWRESET                     */
#define ST7735_READ_ID                      0x04U  /* Read Display ID: RDDID                      */
#define ST7735_READ_STATUS                  0x09U  /* Read Display Statu: RDDST                   */
#define ST7735_READ_POWER_MODE              0x0AU  /* Read Display Power: RDDPM                   */
#define ST7735_READ_MADCTL                  0x0BU  /* Read Display: RDDMADCTL                     */
#define ST7735_READ_PIXEL_FORMAT            0x0CU  /* Read Display Pixel: RDDCOLMOD               */  
#define ST7735_READ_IMAGE_MODE              0x0DU  /* Read Display Image: RDDIM                   */
#define ST7735_READ_SIGNAL_MODE             0x0EU  /* Read Display Signal: RDDSM                  */           
#define ST7735_SLEEP_IN                     0x10U  /* Sleep in & booster off: SLPIN               */ 
#define ST7735_SLEEP_OUT                    0x11U  /* Sleep out & booster on: SLPOUT              */
#define ST7735_PARTIAL_DISPLAY_ON           0x12U  /* Partial mode on: PTLON                      */ 
#define ST7735_NORMAL_DISPLAY_OFF           0x13U  /* Partial off (Normal): NORON                 */
#define ST7735_DISPLAY_INVERSION_OFF        0x20U  /* Display inversion off: INVOFF               */
#define ST7735_DISPLAY_INVERSION_ON         0x21U  /* Display inversion on: INVON                 */
#define ST7735_GAMMA_SET                    0x26U  /* Gamma curve select: GAMSET                  */
#define ST7735_DISPLAY_OFF                  0x28U  /* Display off: DISPOFF                        */
#define ST7735_DISPLAY_ON                   0x29U  /* Display on: DISPON                          */
#define ST7735_CASET                        0x2AU  /* Column address set: CASET                   */ 
#define ST7735_RASET                        0x2BU  /* Row address set: RASET                      */
#define ST7735_RAMWR                        0x2CU  /* Memory write: RAMWR                         */  
#define ST7735_RGBSET                       0x2DU  /* LUT for 4k,65k,262k color: RGBSET           */
#define ST7735_READ_RAM                     0x2EU  /* Memory read: RAMRD                          */
#define ST7735_PTLAR                        0x30U  /* Partial start/end address set: PTLAR        */ 
#define ST7735_TE_LINE_OFF                  0x34U  /* Tearing effect line off: TEOFF              */ 
#define ST7735_TE_LINE_ON                   0x35U  /* Tearing effect mode set & on: TEON          */ 
#define ST7735_MADCTL                       0x36U  /* Memory data access control: MADCTL          */ 
#define ST7735_IDLE_MODE_OFF                0x38U  /* Idle mode off: IDMOFF                       */ 
#define ST7735_IDLE_MODE_ON                 0x39U  /* Idle mode on: IDMON                         */ 
#define ST7735_COLOR_MODE                   0x3AU  /* Interface pixel format: COLMOD              */
#define ST7735_FRAME_RATE_CTRL1             0xB1U  /* In normal mode (Full colors): FRMCTR1       */
#define ST7735_FRAME_RATE_CTRL2             0xB2U  /* In Idle mode (8-colors): FRMCTR2            */   
#define ST7735_FRAME_RATE_CTRL3             0xB3U  /* In partial mode + Full colors: FRMCTR3      */
#define ST7735_FRAME_INVERSION_CTRL         0xB4U  /* Display inversion control: INVCTR           */
#define ST7735_DISPLAY_SETTING              0xB6U  /* Display function setting                    */
#define ST7735_PWR_CTRL1                    0xC0U  /* Power control setting: PWCTR1               */ 
#define ST7735_PWR_CTRL2                    0xC1U  /* Power control setting: PWCTR2               */ 
#define ST7735_PWR_CTRL3                    0xC2U  /* In normal mode (Full colors): PWCTR3        */
#define ST7735_PWR_CTRL4                    0xC3U  /* In Idle mode (8-colors): PWCTR4             */ 
#define ST7735_PWR_CTRL5                    0xC4U  /* In partial mode + Full colors: PWCTR5       */
#define ST7735_VCOMH_VCOML_CTRL1            0xC5U  /* VCOM control 1: VMCTR1                      */ 
#define ST7735_VMOF_CTRL                    0xC7U  /* Set VCOM offset control: VMOFCTR            */ 
#define ST7735_WRID2                        0xD1U  /* Set LCM version code: WRID2                 */ 
#define ST7735_WRID3                        0xD2U  /* Customer Project code: WRID3                */ 
#define ST7735_NV_CTRL1                     0xD9U  /* NVM control status: NVCTR1                  */
#define ST7735_READ_ID1                     0xDAU  /* Read ID1: RDID1                             */ 
#define ST7735_READ_ID2                     0xDBU  /* Read ID2: RDID2                             */ 
#define ST7735_READ_ID3                     0xDCU  /* Read ID3: RDID3                             */ 
#define ST7735_NV_CTRL2                     0xDEU  /* NVM Read Command: NVCTR2                    */ 
#define ST7735_NV_CTRL3                     0xDFU  /* NVM Write Command: NVCTR3                   */
#define ST7735_PV_GAMMA_CTRL                0xE0U  /* Set Gamma adjustment (+ polarity): GAMCTRP1 */
#define ST7735_NV_GAMMA_CTRL                0xE1U  /* Set Gamma adjustment (- polarity): GAMCTRN1 */
#define ST7735_EXT_CTRL                     0xF0U  /* Extension command control                   */
#define ST7735_PWR_CTRL6                    0xFCU  /* In partial mode + Idle mode: PWCTR6         */
#define ST7735_VCOM4_LEVEL                  0xFFU  /* VCOM 4 level control                        */

#define ST7735_FORMAT_RBG444                0x03U /* Pixel format chosen is RGB444 : 12 bpp */   
#define ST7735_FORMAT_RBG565                0x05U /* Pixel format chosen is RGB565 : 16 bpp */
#define ST7735_FORMAT_RBG666                0x06U /* Pixel format chosen is RGB666 : 18 bpp */

#define ST7735_ORIENTATION_PORTRAIT         0x00U /* Portrait orientation choice of LCD screen               */
#define ST7735_ORIENTATION_PORTRAIT_ROT180  0xC0U /* Portrait rotated 180� orientation choice of LCD screen  */
#define ST7735_ORIENTATION_LANDSCAPE        0x70U /* Landscape orientation choice of LCD screen              */
#define ST7735_ORIENTATION_LANDSCAPE_ROT180 0xA0U /* Landscape rotated 180� orientation choice of LCD screen */
/**********************
 *      DEFINES
 **********************/ 
#define LOG_PRINTF_ST7735

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
void panel_st7735_prepare()
{

}

void panel_st7735_fill_point()
{

}

void panel_st7735_fill_rectangle()
{

}

void panel_st7735_flush()
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



 







