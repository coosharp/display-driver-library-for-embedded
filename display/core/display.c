/**
 * @file display.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "display.h"
#include "./common/display_log.h"
/*********************
 *      MACROS
 *********************/

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
void display_register_instance(struct display * self, 
                               const struct display_painter ** painter, 
                               const struct display_backlight ** backlight)
{
    self->painter = painter;
    self->backlight = backlight;
}


/*---------------------
 *      Painter
 *--------------------*/
void display_fill_point(const struct display * self, 
                        uint16_t x, 
                        uint16_t y)
{
    fill_point_fn_t fn = (*self->painter)->fill_point;
    uint32_t color = self->context.color;
    if(fn)
        fn(self->painter, x, y, color);

    LOG_INFO_DISPLAY("Filled point at (%d, %d) with color 0x%X", x, y, color);
}

void display_fill_rectangle(const struct display * self, 
                             uint16_t x, 
                             uint16_t y, 
                             uint16_t w, 
                             uint16_t h)
{
    fill_rectangle_fn_t fn = (*self->painter)->fill_rectangle;
    uint32_t color = self->context.color;
    if(fn)
        fn(self->painter, x, y, w, h, color);

    LOG_INFO_DISPLAY("Filled rectangle at (%d, %d) with width %d and height %d with color 0x%X", x, y, w, h, color);
}

void display_flush(const struct display * self, 
                   uint16_t x1, 
                   uint16_t y1, 
                   uint16_t x2, 
                   uint16_t y2, 
                   const void * data)
{
    flush_fn_t fn = (*self->painter)->flush;
    
    if(fn)
        fn(self->painter, x1, y1, x2, y2, data);

    LOG_INFO_DISPLAY("Flushed area from (%d, %d) to (%d, %d)", x1, y1, x2, y2);
}

void display_set_color(struct display * self, 
                             uint32_t color)
{
    self->context.color = color;

    LOG_INFO_DISPLAY("Set brush color to 0x%X", color);
}

void display_draw_line(const struct display * self, 
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
        display_fill_point(self, x1, y1);
        
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

void display_draw_triangle(const struct display * self,
                                uint16_t x1,
                                uint16_t y1,
                                uint16_t x2,
                                uint16_t y2,
                                uint16_t x3,
                                uint16_t y3)
{
    display_draw_line(self, x1, y1, x2, y2);
    display_draw_line(self, x2, y2, x3, y3);
    display_draw_line(self, x3, y3, x1, y1);
}

void display_draw_rectangle(const struct display * self,
                             uint16_t x,
                             uint16_t y,
                             uint16_t w,
                             uint16_t h)
{
    display_draw_line(self, x, y, x + w, y);
    display_draw_line(self, x + w, y, x + w, y + h);
    display_draw_line(self, x + w, y + h, x, y + h);
    display_draw_line(self, x, y + h, x, y);
}

void display_draw_circle(const struct display * self,
                          uint16_t x,
                          uint16_t y,
                          uint16_t r)
{
    int x_add = -r, yadd = 0, err = 2 - 2 * r, e2;
    do {   
        display_fill_point(self, x - x_add, y + yadd);
        display_fill_point(self, x + x_add, y + yadd);
        display_fill_point(self, x + x_add, y - yadd);
        display_fill_point(self, x - x_add, y - yadd);

        e2 = err;
        if (e2 <= yadd) {
            err += ++yadd * 2 + 1;
            if (-x_add == yadd && e2 <= x_add) e2 = 0;
        }
        if (e2 > x_add) err += ++x_add * 2 + 1;
    }
    while (x_add <= 0);
}

void display_draw_ellipse(const struct display * self,
                               uint16_t x,
                               uint16_t y,
                               uint16_t rx,
                               uint16_t ry)
{
    int32_t x_add = -rx, y_add = 0, err = 2 - 2 * rx, e2;
    float K = 0, rad1 = 0, rad2 = 0;

    rad1 = rx;
    rad2 = ry;

    if (rx > ry)
    { 
        do {
            K = (float)(rad1/rad2);

            display_fill_point(self, x - x_add, y + (uint16_t)(y_add / K));
            display_fill_point(self, x + x_add, y + (uint16_t)(y_add / K));
            display_fill_point(self, x + x_add, y - (uint16_t)(y_add / K));
            display_fill_point(self, x - x_add, y - (uint16_t)(y_add / K));

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

            display_fill_point(self, x - (uint16_t)(x_add / K), y + y_add);
            display_fill_point(self, x + (uint16_t)(x_add / K), y + y_add);
            display_fill_point(self, x + (uint16_t)(x_add / K), y - y_add);
            display_fill_point(self, x - (uint16_t)(x_add / K), y - y_add);

            e2 = err;
            if (e2 <= x_add) {
                err += ++x_add * 2 + 1;
                if (-y_add == x_add && e2 <= y_add) e2 = 0;
            }
            if (e2 > y_add) err += ++y_add * 2 + 1;
        }
        while (y_add <= 0);
    }
}


/*---------------------
 *      Backlight
 *--------------------*/
void display_enable_backlight(const struct display * self)
{
    enable_backlight_fn_t fn = (*self->backlight)->enable_backlight;

    if(fn)
        fn(self->backlight);
}

void display_disable_backlight(const struct display * self)
{
    disable_backlight_fn_t fn = (*self->backlight)->disable_backlight;

    if(fn)
        fn(self->backlight);
}

void display_set_backlight_brightness(const struct display * self, uint8_t brightness)
{
    set_backlight_brightness_fn_t fn = (*self->backlight)->set_backlight_brightness;

    if(fn)
        fn(self->backlight, brightness);

    LOG_INFO_DISPLAY("Set backlight brightness to %d", brightness);
}



/**********************
 *   STATIC FUNCTIONS
 **********************/



/******************************* (END OF FILE) *********************************/



 












