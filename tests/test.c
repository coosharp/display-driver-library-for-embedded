#include "display.h"



int main(void)
{

    struct display display_instance;


    display_register_instance(&display_instance, NULL, NULL);

    return 0;
}