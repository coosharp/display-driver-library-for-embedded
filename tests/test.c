#include "sgfx_display.h"



int main(void)
{

    struct sgfx_display display_instance;


    sgfx_display_register_instance(&display_instance, NULL, NULL);

    return 0;
}