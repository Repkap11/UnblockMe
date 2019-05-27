#include "move_command.hpp"
#include "logging.hpp"

void move_command_print( const MoveCommand &move ) {
    pr( "Slide %c %s by %d", move.which_block, move.dir, move.size );
}
