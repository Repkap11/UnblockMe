#include "move_command.hpp"
#include "logging.hpp"
#include <stdio.h>

void move_command_print( const MoveCommand &move ) {
    const char* dir = "Error";
    if (move.dir_x == 1 ) dir = "right";
    if (move.dir_x == -1 ) dir = "left";
    if (move.dir_y == 1 ) dir = "down";
    if (move.dir_y == -1 ) dir = "up";
    pr( "Slide %c %s by %d", move.which_block, dir, move.size );
}

void move_command_append( const MoveCommand &move, FILE *f ) {
    fprintf( f, "%c,%d,%d,%d,%d,%d\n", move.which_block, move.j, move.i, move.dir_x, move.dir_y, move.size );
}
