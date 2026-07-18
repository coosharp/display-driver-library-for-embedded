/**
 * @file display.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "sgfx_display.h"
#include "sgfx_log.h"
/*********************
 *      MACROS
 *********************/
#if SGFX_LOG_DISPLAY_ENABLE
    #define LOG_TRACE_DISPLAY(fmt, ...)  SGFX_LOG_TRACE(fmt, ##__VA_ARGS__)
    #define LOG_INFO_DISPLAY(fmt, ...)   SGFX_LOG_INFO(fmt, ##__VA_ARGS__)
    #define LOG_WARN_DISPLAY(fmt, ...)   SGFX_LOG_WARN(fmt, ##__VA_ARGS__)
    #define LOG_ERROR_DISPLAY(fmt, ...)  SGFX_LOG_ERROR(fmt, ##__VA_ARGS__)
#else
    #define LOG_TRACE_DISPLAY(fmt, ...)  do{} while(0)
    #define LOG_INFO_DISPLAY(fmt, ...)   do{} while(0)
    #define LOG_WARN_DISPLAY(fmt, ...)   do{} while(0)
    #define LOG_ERROR_DISPLAY(fmt, ...)  do{} while(0)
#endif /* SGFX_LOG_DISPLAY_ENABLE */

/**********************
 *   GLOBAL VARIABLES
 **********************/ 

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 

/*---------------------
*      Register
*--------------------*/
void sgfx_display_register(struct sgfx_display * self, 
                            const struct sgfx_display_drawing ** drawing, 
                            const struct sgfx_display_backlight ** backlight)
{
    self->drawing = drawing;
    self->backlight = backlight;
    self->context.color = 0xFFFFFFFF; /* Default color: white */

    LOG_INFO_DISPLAY("Display instance registered with drawing: %p and backlight: %p", (const void *)drawing, (const void *)backlight);
}


/*---------------------
 *      Drawing
 *--------------------*/
void sgfx_display_fill_point(const struct sgfx_display * self, 
                        uint16_t x, 
                        uint16_t y)
{
    display_fill_point_fn_t fn = (*self->drawing)->fill_point;

    uint32_t color = self->context.color;

    if(fn) {
        LOG_INFO_DISPLAY("Filled point at (%d, %d) with color 0x%X", x, y, color);
        fn(self->drawing, x, y, color);
    }
    else {
        LOG_WARN_DISPLAY("Fill point function not implemented!");
    }
}

void sgfx_display_fill_rectangle(const struct sgfx_display * self, 
                             uint16_t x, 
                             uint16_t y, 
                             uint16_t w, 
                             uint16_t h)
{
    display_fill_rectangle_fn_t fn = (*self->drawing)->fill_rectangle;

    uint32_t color = self->context.color;

    if(fn) {
        LOG_INFO_DISPLAY("Filled rectangle at (%d, %d) with width %d and height %d with color 0x%X", x, y, w, h, color);
        fn(self->drawing, x, y, w, h, color);
    }
    else {
        LOG_WARN_DISPLAY("Fill rectangle function not implemented!");
    }    
}

void sgfx_display_flush(const struct sgfx_display * self, 
                   uint16_t x1, 
                   uint16_t y1, 
                   uint16_t x2, 
                   uint16_t y2, 
                   const void * data)
{
    display_flush_fn_t fn = (*self->drawing)->flush;
    
    if(fn) {
        LOG_INFO_DISPLAY("Flushed area from (%d, %d) to (%d, %d)", x1, y1, x2, y2);
        fn(self->drawing, x1, y1, x2, y2, data);
    }
    else {
        LOG_WARN_DISPLAY("Flush function not implemented!");
    }
}

void sgfx_display_set_color(struct sgfx_display * self, 
                             uint32_t color)
{
    self->context.color = color;

    LOG_INFO_DISPLAY("Set brush color to 0x%X", color);
}

void sgfx_display_draw_line(const struct sgfx_display * self, 
                       uint16_t x1, 
                       uint16_t y1, 
                       uint16_t x2, 
                       uint16_t y2)
{
    LOG_TRACE_DISPLAY("Begin!");

    LOG_INFO_DISPLAY("Drawing line from (%d, %d) to (%d, %d)", x1, y1, x2, y2);

    int32_t dx = 0;
    int32_t dy = 0;
    int32_t sx = 0;
    int32_t sy = 0;
    int32_t err = 0;
    int32_t e2 = 0;                         
    
    dx = x2 - x1;
    dx = ((dx) > 0 ? (dx) : -(dx));

    dy = y2 - y1;
    dy = ((dy) > 0 ? (dy) : -(dy));

    if(x1 < x2) {
        sx = 1;
    } 
    else {
        sx = -1;
    }
    
    if(y1 < y2) {
        sy = 1;
    } 
    else {
        sy = -1;
    }
    
    err = dx - dy;
    
    while(1) {
        sgfx_display_fill_point(self, x1, y1);
        
        if(x1 == x2 && y1 == y2) {
            break;
        }
        
        e2 = 2 * err;
        
        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        
        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    LOG_TRACE_DISPLAY("End!");
}

void sgfx_display_draw_triangle(const struct sgfx_display * self,
                                uint16_t x1,
                                uint16_t y1,
                                uint16_t x2,
                                uint16_t y2,
                                uint16_t x3,
                                uint16_t y3)
{
    sgfx_display_draw_line(self, x1, y1, x2, y2);
    sgfx_display_draw_line(self, x2, y2, x3, y3);
    sgfx_display_draw_line(self, x3, y3, x1, y1);
}

void sgfx_display_draw_rectangle(const struct sgfx_display * self,
                             uint16_t x,
                             uint16_t y,
                             uint16_t w,
                             uint16_t h)
{
    sgfx_display_draw_line(self, x, y, x + w, y);
    sgfx_display_draw_line(self, x + w, y, x + w, y + h);
    sgfx_display_draw_line(self, x + w, y + h, x, y + h);
    sgfx_display_draw_line(self, x, y + h, x, y);
}

void sgfx_display_draw_circle(const struct sgfx_display * self,
                          uint16_t x,
                          uint16_t y,
                          uint16_t r)
{
    LOG_TRACE_DISPLAY("Begin!");

    int x_add = -r, yadd = 0, err = 2 - 2 * r, e2;
    do {   
        sgfx_display_fill_point(self, x - x_add, y + yadd);
        sgfx_display_fill_point(self, x + x_add, y + yadd);
        sgfx_display_fill_point(self, x + x_add, y - yadd);
        sgfx_display_fill_point(self, x - x_add, y - yadd);

        e2 = err;
        if (e2 <= yadd) {
            err += ++yadd * 2 + 1;
            if (-x_add == yadd && e2 <= x_add) e2 = 0;
        }
        if (e2 > x_add) err += ++x_add * 2 + 1;
    }
    while (x_add <= 0);

    LOG_TRACE_DISPLAY("End!");
}

void sgfx_display_draw_ellipse(const struct sgfx_display * self,
                               uint16_t x,
                               uint16_t y,
                               uint16_t rx,
                               uint16_t ry)
{
    LOG_TRACE_DISPLAY("Begin!");

    int32_t x_add = -rx, y_add = 0, err = 2 - 2 * rx, e2;
    float K = 0, rad1 = 0, rad2 = 0;

    rad1 = rx;
    rad2 = ry;

    if (rx > ry)
    { 
        do {
            K = (float)(rad1/rad2);

            sgfx_display_fill_point(self, x - x_add, y + (uint16_t)(y_add / K));
            sgfx_display_fill_point(self, x + x_add, y + (uint16_t)(y_add / K));
            sgfx_display_fill_point(self, x + x_add, y - (uint16_t)(y_add / K));
            sgfx_display_fill_point(self, x - x_add, y - (uint16_t)(y_add / K));

            e2 = err;
            if (e2 <= y_add) {
                err += ++y_add * 2 + 1;
                if (-x_add == y_add && e2 <= x_add) e2 = 0;
            }
            if (e2 > x_add) err += ++x_add * 2 + 1;
        }
        while (x_add <= 0);
    }
    else
    {
        y_add = -ry; 
        x_add = 0;
        do { 
            K = (float)(rad2/rad1);

            sgfx_display_fill_point(self, x - (uint16_t)(x_add / K), y + y_add);
            sgfx_display_fill_point(self, x + (uint16_t)(x_add / K), y + y_add);
            sgfx_display_fill_point(self, x + (uint16_t)(x_add / K), y - y_add);
            sgfx_display_fill_point(self, x - (uint16_t)(x_add / K), y - y_add);

            e2 = err;
            if (e2 <= x_add) {
                err += ++x_add * 2 + 1;
                if (-y_add == x_add && e2 <= y_add) e2 = 0;
            }
            if (e2 > y_add) err += ++y_add * 2 + 1;
        }
        while (y_add <= 0);
    }

    LOG_TRACE_DISPLAY("End!");
}

int sgfx_display_ioctrl(const struct sgfx_display * self, uint32_t command, void * arg)
{
    LOG_TRACE_DISPLAY("Begin!");

    int result = -1;

    display_ioctrl_fn_t fn = (*self->drawing)->ioctrl;

    LOG_INFO_DISPLAY("Performing ioctrl command: %d", command);

    if(fn) {
        result = fn(self->drawing, command, arg);
    }
    else {
        LOG_WARN_DISPLAY("Drawing ioctrl function not implemented!");
    }

    LOG_TRACE_DISPLAY("End!");

    return result;
}

/*---------------------
 *      Backlight
 *--------------------*/
void sgfx_display_set_backlight_state(const struct sgfx_display * self, uint8_t state)
{
    LOG_TRACE_DISPLAY("Begin!");

    display_set_backlight_state_fn_t fn = (*self->backlight)->set_backlight_state;

    if(fn) {
        LOG_INFO_DISPLAY("Set backlight state to %d", state);
        fn(self->backlight, state);
    }
    else {
        LOG_WARN_DISPLAY("Set backlight state function not implemented!");
    }

    LOG_TRACE_DISPLAY("End!");
}

void sgfx_display_get_backlight_state(const struct sgfx_display * self, uint8_t * state)
{
    LOG_TRACE_DISPLAY("Begin!");

    display_get_backlight_state_fn_t fn = (*self->backlight)->get_backlight_state;

    if(fn) {
        fn(self->backlight, state);
        LOG_INFO_DISPLAY("Got backlight state: %d", *state);
    }
    else {
        LOG_WARN_DISPLAY("Get backlight state function not implemented!");
    }

    LOG_TRACE_DISPLAY("End!");
}

void sgfx_display_set_backlight_brightness(const struct sgfx_display * self, uint8_t brightness)
{
    LOG_TRACE_DISPLAY("Begin!");

    display_set_backlight_brightness_fn_t fn = (*self->backlight)->set_backlight_brightness;

    if(fn) {
        LOG_INFO_DISPLAY("Set backlight brightness to %d", brightness);
        fn(self->backlight, brightness);
    }
    else {
        LOG_WARN_DISPLAY("Set backlight brightness function not implemented!");
    }

    LOG_TRACE_DISPLAY("End!");
}

void sgfx_display_get_backlight_brightness(const struct sgfx_display * self, uint8_t * brightness)
{
    LOG_TRACE_DISPLAY("Begin!");

    display_get_backlight_brightness_fn_t fn = (*self->backlight)->get_backlight_brightness;

    if(fn) {
        fn(self->backlight, brightness);
        LOG_INFO_DISPLAY("Got backlight brightness: %d", *brightness);
    }
    else {
        LOG_WARN_DISPLAY("Get backlight brightness function not implemented!");
    }

    LOG_TRACE_DISPLAY("End!");
}



/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 












