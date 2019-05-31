#include "move_command.hpp"
#include "logging.hpp"
#include <stdio.h>

void move_command_print( const MoveCommand &move ) {
    pr( "Slide %c %s by %d", move.which_block, move.dir, move.size );
}

void move_command_append( const MoveCommand &move, FILE *f ) {
    fprintf( f, "Slide %c (%d %d) %s by %d\n", move.which_block, move.i, move.j, move.dir, move.size );
}
