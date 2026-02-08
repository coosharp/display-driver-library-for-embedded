/**
 * @file disp_painter.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "../display.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void disp_painter_set_brush_color(struct display * self, 
                                  uint32_t color)
{
    self->ctx.brush_color = color;
}

void disp_painter_fill_point(const struct display * self, 
                             uint16_t x, 
                             uint16_t y)
{
    fill_point_fn_t fn = (*self->painter)->fill_point;
    uint32_t color = self->ctx.brush_color;
    if(fn)
        fn(self->painter, x, y, color);
}

void disp_painter_fill_rectangle(const struct display * self, 
                                 uint16_t x, 
                                 uint16_t y, 
                                 uint16_t w, 
                                 uint16_t h)
{
    fill_rectangle_fn_t fn = (*self->painter)->fill_rectangle;
    uint32_t color = self->ctx.brush_color;
    if(fn)
        fn(self->painter, x, y, w, h, color);
}

void disp_painter_flush(const struct display * self, 
                        uint16_t x1, 
                        uint16_t y1, 
                        uint16_t x2, 
                        uint16_t y2, 
                        const void * data)
{
    flush_fn_t fn = (*self->painter)->flush;
    
    if(fn)
        fn(self->painter, x1, y1, x2, y2, data);
}

void disp_painter_draw_line(const struct display * self, 
                            uint16_t x1, 
                            uint16_t y1, 
                            uint16_t x2, 
                            uint16_t y2)
{
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
        disp_painter_fill_point(self, x1, y1);
        
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
}

void disp_painter_draw_triangle(const struct display * self,
                                uint16_t x1,
                                uint16_t y1,
                                uint16_t x2,
                                uint16_t y2,
                                uint16_t x3,
                                uint16_t y3)
{
    disp_painter_draw_line(self, x1, y1, x2, y2);
    disp_painter_draw_line(self, x2, y2, x3, y3);
    disp_painter_draw_line(self, x3, y3, x1, y1);
}

void disp_painter_draw_rectangle(const struct display * self,
                                 uint16_t x,
                                 uint16_t y,
                                 uint16_t w,
                                 uint16_t h)
{
    disp_painter_draw_line(self, x, y, x + w, y);
    disp_painter_draw_line(self, x + w, y, x + w, y + h);
    disp_painter_draw_line(self, x + w, y + h, x, y + h);
    disp_painter_draw_line(self, x, y + h, x, y);
}           

void disp_painter_draw_circle(const struct display * self,
                              uint16_t x,
                              uint16_t y,
                              uint16_t r)
{
    int x_add = -r, yadd = 0, err = 2 - 2 * r, e2;
    do {   
        disp_painter_fill_point(self, x - x_add, y + yadd);
        disp_painter_fill_point(self, x + x_add, y + yadd);
        disp_painter_fill_point(self, x + x_add, y - yadd);
        disp_painter_fill_point(self, x - x_add, y - yadd);

        e2 = err;
        if (e2 <= yadd) {
            err += ++yadd * 2 + 1;
            if (-x_add == yadd && e2 <= x_add) e2 = 0;
        }
        if (e2 > x_add) err += ++x_add * 2 + 1;
    }
    while (x_add <= 0);
}

void disp_painter_draw_ellipse(const struct display * self,
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

            disp_painter_fill_point(self, x - x_add, y + (uint16_t)(y_add / K));
            disp_painter_fill_point(self, x + x_add, y + (uint16_t)(y_add / K));
            disp_painter_fill_point(self, x + x_add, y - (uint16_t)(y_add / K));
            disp_painter_fill_point(self, x - x_add, y - (uint16_t)(y_add / K));

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

            disp_painter_fill_point(self, x - (uint16_t)(x_add / K), y + y_add);
            disp_painter_fill_point(self, x + (uint16_t)(x_add / K), y + y_add);
            disp_painter_fill_point(self, x + (uint16_t)(x_add / K), y - y_add);
            disp_painter_fill_point(self, x - (uint16_t)(x_add / K), y - y_add);

            e2 = err;
            if (e2 <= x_add) {
                err += ++x_add * 3 + 1;
                if (-y_add == x_add && e2 <= y_add) e2 = 0;
            }
            if (e2 > y_add) err += ++y_add * 3 + 1;
        }
        while (y_add <= 0);
    }
}


/******************************* (END OF FILE) *********************************/



 







