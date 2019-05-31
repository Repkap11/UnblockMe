#pragma once
#include <stdio.h>

typedef struct MoveCommand {
    int i, j;
    char which_block;
    int dir_x;
    int dir_y;
    int size;
    MoveCommand( ) : i( -1 ), j( -1 ), which_block( '-' ), dir_x( 0 ), dir_y( 0 ) {
    }
    MoveCommand( int i, int j, char which_block, int dir_x, int dir_y, int size ) : i( i ), j( j ), which_block( which_block ), dir_x( dir_x ), dir_y( dir_y ), size(size) {
    }
} MoveCommand;

void move_command_print( const MoveCommand &move );
void move_command_append( const MoveCommand &move, FILE *f );
