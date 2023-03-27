//
// Created by buryhugo on 27/03/23.
//
//

// \file main.c
//
// \brief Source code example for Alambix programming.
//

#include "alambix.h"
#include <stdlib.h>

void alambix_init()
{
    // TODO: Insert initialization code here.
}

void alambix_help()
{
    char* help_path = alambix_help_html();
    system(help_path);
    free(help_path);
}

int main(int argc, char * argv[])
{
    alambix_open();
    alambix_help(); // Launch the Alambix help documentation in a browser.


    // TODO: Insert cleanup code here.

    return alambix_close();
}