#pragma once
#include <stdio.h>

typedef struct MoveCommand {
    int i, j;
    char which_block;
    const char *dir;
    int size;
    MoveCommand( ) : i( -1 ), j( -1 ), which_block( '-' ), dir( "Error" ) {
    }
    MoveCommand( int i, int j, char which_block, const char *dir, int size ) : i( i ), j( j ), which_block( which_block ), dir( dir ), size( size ) {
    }
} MoveCommand;

void move_command_print( const MoveCommand &move );
void move_command_append( const MoveCommand &move, FILE *f );
