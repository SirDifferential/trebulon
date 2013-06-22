#include <stdio.h>
#include "game.hpp"

int main(int argc, char** argv)
{
    fprintf(stderr, "# Main\n");
    game.start();
    return game.mainloop();
}

