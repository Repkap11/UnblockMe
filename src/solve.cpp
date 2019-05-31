#include "logging.hpp"
#include "map.hpp"
#include "map_hash_table.hpp"
#include <cstdlib>
#include <stdio.h>

TableElement *extend_tip( Table &table );
void add_successors( Table &table, const Map &map );
bool is_solution( const Map &map );

TableElement *tip;
Table globalTable; // Rely in initilzation to zero.
int num_tips = 0;

#define BUFF_SIZE 100
int main( int argc, char **argv ) {
    char *solution_file = NULL;
    char *input_file = NULL;
    if ( argc == 3 ) {
        input_file = argv[ 1 ];
        solution_file = argv[ 2 ];
    } else if ( argc == 2 ) {
        input_file = argv[ 1 ];
        solution_file = NULL;
    } else {
        // pr( "usage %s input_level_file output_solution_file", argv[ 0 ] );
        // return 1;
    }
    char *input = 0;
    long length;
    FILE *f = NULL;
    if ( input_file != NULL ) {
        f = fopen( input_file, "rb" );
        if ( f ) {
            fseek( f, 0, SEEK_END );
            length = ftell( f );
            fseek( f, 0, SEEK_SET );
            input = ( char * )malloc( length );
            if ( input ) {
                fread( input, 1, length, f );
            }
            fclose( f );
        }
        if ( !input ) {
            pr( "Could not read file:%s", input_file );
            return 1;
        }
    }

    if ( !input ) {
        input = ( char * )"a...cd\n"
                          "abbbcd\n"
                          "kkgfed\n"
                          "llgfe.\n"
                          "...hii\n"
                          "...hjj";
    }

    Map starting_map;
    map_populate_from_chars( starting_map, input );

    // map_print_slide( starting_map );
    map_print_which_block( starting_map );
    // map_print_size( starting_map );

    map_hash_table_add_map_if_unique( globalTable, starting_map, MoveCommand( ), NULL );
    tip = new TableElement( );
    tip->map = starting_map;
    tip->parent = NULL;
    tip->next = new TableElement( );
    TableElement *solution = extend_tip( globalTable );
    pr( "Used num_tips:%d", num_tips );
    if ( solution != NULL ) {
        pr( "Found Solution" );
        map_hash_table_print_solution( globalTable, solution->map, solution_file );
    } else {
        pr( "Ran out of tips without finding a solution" );
    }
    // TODO free all the tips...
}

bool is_solution( const Map &map ) {
    return map.grids[ 2 ][ 5 ].slide == SLIDE_HORIZONTAL;
}

TableElement *extend_tip( Table &table ) {
    TableElement *element = tip;
    while ( element != NULL ) { // While the tip isn't the last tip.
        if ( is_solution( element->map ) ) {
            return element;
        }
        add_successors( table, element->map );
        TableElement *old_element = element;
        element = element->next;
        delete old_element;
    }
    return NULL;
}

void add_successor_map( Table &table, const Map &map, const MoveCommand &move, const Map &parent ) {

    bool was_added = map_hash_table_add_map_if_unique( table, map, move, &parent );
    if ( was_added ) {
        // map_print_which_block( map );
        // pr( "Wait for Press" );
        // getchar( );
        TableElement *element = new TableElement( move );
        element->next = NULL;
        element->map = map;
        num_tips++;
        // if ( num_tips == 68 ) {
        // pr( "Num_Tips:%d", num_tips );
        //}
        tip->next = element;
        tip = element;
    }
}

void add_successors( Table &table, const Map &map ) {
    for ( int i = 0; i < 6; i++ ) {
        for ( int j = 0; j < 6; j++ ) {
            const Grid *grid = &map.grids[ i ][ j ];
            const char c = grid->which_block;
            if ( c == ' ' ) {
                continue;
            }
            int size = grid->size;
            if ( grid->slide == SILDE_VERTICAL ) {
                if ( i != 0 ) {
                    if ( map.grids[ i - 1 ][ j ].which_block == c ) {
                        // This is an extention of the block above, so don't do anything vertically
                        continue;
                    }
                    int max_move = i;
                    bool done = false;
                    for ( int a = 1; ( !done ) && ( a < max_move + 1 ); a++ ) {
                        // pr( "Trying Move Up:%d", a );
                        Map new_map = map;
                        MoveCommand move( i, j, c, 0, -1, a );
                        for ( int b = 1; ( !done ) && ( b < a + 1 ); b++ ) {
                            if ( new_map.grids[ i - b ][ j ].which_block != ' ' ) {
                                done = true;
                                break;
                            }
                            // pr( "  Adjusting i=%d and i=%d", i - b, i + size - b );
                            new_map.grids[ i - b ][ j ].which_block = c;
                            new_map.grids[ i - b ][ j ].size = size;
                            new_map.grids[ i - b ][ j ].slide = SILDE_VERTICAL;

                            new_map.grids[ i + size - b ][ j ].which_block = ' ';
                            new_map.grids[ i + size - b ][ j ].size = 0;
                            new_map.grids[ i + size - b ][ j ].slide = SILDE_NONE;
                        }
                        if ( !done ) {
                            add_successor_map( table, new_map, move, map );
                        }
                    }
                }
                int max_move = 6 - ( i + size );
                bool done = false;
                for ( int a = 1; ( !done ) && ( a < max_move + 1 ); a++ ) {
                    // pr( "Trying Move Down:%d", a );
                    Map new_map = map;
                    MoveCommand move( i, j, c, 0, 1, a );
                    for ( int b = 0; ( !done ) && ( b < a ); b++ ) {
                        if ( new_map.grids[ i + size + b ][ j ].which_block != ' ' ) {
                            done = true;
                            break;
                        }
                        // pr( "  Adjusting j=%d and j=%d", j + b, j + size + b );
                        new_map.grids[ i + b ][ j ].which_block = ' ';
                        new_map.grids[ i + b ][ j ].size = 0;
                        new_map.grids[ i + b ][ j ].slide = SILDE_NONE;

                        new_map.grids[ i + size + b ][ j ].which_block = c;
                        new_map.grids[ i + size + b ][ j ].size = size;
                        new_map.grids[ i + size + b ][ j ].slide = SILDE_VERTICAL;
                    }
                    if ( !done ) {
                        add_successor_map( table, new_map, move, map );
                    }
                }
            }
            if ( grid->slide == SLIDE_HORIZONTAL ) {
                if ( j != 0 ) {
                    if ( map.grids[ i ][ j - 1 ].which_block == c ) {
                        // This is an extention of the block to the left, so don't do anything horiziontally
                        continue;
                    }
                    int max_move = j;
                    bool done = false;
                    for ( int a = 1; ( !done ) && ( a < max_move + 1 ); a++ ) {
                        // pr( "Trying Move Left:%d", a );
                        Map new_map = map;
                        MoveCommand move( i, j, c, -1, 0, a );
                        for ( int b = 1; ( !done ) && ( b < a + 1 ); b++ ) {
                            if ( new_map.grids[ i ][ j - b ].which_block != ' ' ) {
                                done = true;
                                break;
                            }
                            // pr( "  Adjusting j=%d and j=%d", j - b, j + size - b );
                            new_map.grids[ i ][ j - b ].which_block = c;
                            new_map.grids[ i ][ j - b ].size = size;
                            new_map.grids[ i ][ j - b ].slide = SLIDE_HORIZONTAL;

                            new_map.grids[ i ][ j + size - b ].which_block = ' ';
                            new_map.grids[ i ][ j + size - b ].size = 0;
                            new_map.grids[ i ][ j + size - b ].slide = SILDE_NONE;
                        }
                        if ( !done ) {
                            add_successor_map( table, new_map, move, map );
                        }
                    }
                }
                int max_move = 6 - ( j + size );
                bool done = false;
                for ( int a = 1; ( !done ) && ( a < max_move + 1 ); a++ ) {
                    // pr( "Trying Move Right:%d", a );
                    Map new_map = map;
                    MoveCommand move( i, j, c, 1, 0, a );
                    for ( int b = 0; ( !done ) && ( b < a ); b++ ) {
                        if ( new_map.grids[ i ][ j + size + b ].which_block != ' ' ) {
                            done = true;
                            break;
                        }
                        // pr( "  Adjusting j=%d and j=%d", j + b, j + size + b );
                        new_map.grids[ i ][ j + b ].which_block = ' ';
                        new_map.grids[ i ][ j + b ].size = 0;
                        new_map.grids[ i ][ j + b ].slide = SILDE_NONE;

                        new_map.grids[ i ][ j + size + b ].which_block = c;
                        new_map.grids[ i ][ j + size + b ].size = size;
                        new_map.grids[ i ][ j + size + b ].slide = SLIDE_HORIZONTAL;
                    }
                    if ( !done ) {
                        add_successor_map( table, new_map, move, map );
                    }
                }
            }
        }
    }
}
