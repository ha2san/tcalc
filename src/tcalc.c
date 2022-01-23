#define _XOPEN_SOURCE 700
#include "input.h"

int main(int argc, char *argv[])
{
    if(argc > 1) {
        run_argument(argv[1]);
    } else {
        run_stdin();
    }
    return EXIT_SUCCESS;
}

