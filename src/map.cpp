#include "map.hpp"
#include "grid.hpp"
#include "solve.hpp"

void map_print_slide( const Map &map ) {
    pr( "" );
    pr( "--Slide-" );
    pr( "┌──────┐" );
    for ( int i = 0; i < 6; i++ ) {
        const Grid *line = map.grids[ i ];
        const char *end_char = i == 2 ? " " : "│";
        pr( "│%c%c%c%c%c%c%s", grid_get_slide_char( line[ 0 ] ), grid_get_slide_char( line[ 1 ] ), grid_get_slide_char( line[ 2 ] ), grid_get_slide_char( line[ 3 ] ), grid_get_slide_char( line[ 4 ] ), grid_get_slide_char( line[ 5 ] ),
            end_char );
    }
    pr( "└──────┘" );
}

void map_print_which_block( const Map &map ) {
    pr( "" );
    pr( "--Block-" );
    pr( "┌──────┐" );
    for ( int i = 0; i < 6; i++ ) {
        const Grid *line = map.grids[ i ];
        const char *end_char = i == 2 ? " " : "│";
        pr( "│%c%c%c%c%c%c%s", grid_get_which_block( line[ 0 ] ), grid_get_which_block( line[ 1 ] ), grid_get_which_block( line[ 2 ] ), grid_get_which_block( line[ 3 ] ), grid_get_which_block( line[ 4 ] ), grid_get_which_block( line[ 5 ] ),
            end_char );
    }
    pr( "└──────┘" );
}
void map_populate_from_chars( Map &starting_map, const char *input ) {
    char input_line[ 6 ][ 6 ];
    sscanf( input, "%6s\n%6s\n%6s\n%6s\n%6s\n%6s", input_line[ 0 ], input_line[ 1 ], input_line[ 2 ], input_line[ 3 ], input_line[ 4 ], input_line[ 5 ] );

    for ( int i = 0; i < 6; i++ ) {
        for ( int j = 0; j < 6; j++ ) {
            char c = input_line[ i ][ j ];
            if ( c != '.' ) {
                starting_map.grids[ i ][ j ].which_block = c;

                bool handled = false;

                if ( i != 0 ) {
                    if ( input_line[ i - 1 ][ j ] == c ) {
                        // This is an extention of the grid above
                        starting_map.grids[ i ][ j ].slide = starting_map.grids[ i - 1 ][ j ].slide;
                        handled = true;
                    }
                }
                if ( j != 0 ) {
                    if ( input_line[ i ][ j - 1 ] == c ) {
                        // This is an extention of the grid to the left
                        starting_map.grids[ i ][ j ].slide = starting_map.grids[ i ][ j - 1 ].slide;
                        handled = true;
                    }
                }
                if ( !handled ) {
                    if ( i != 5 ) {
                        if ( input_line[ i + 1 ][ j ] == c ) {
                            starting_map.grids[ i ][ j ].slide = SILDE_VERTICAL;
                            handled = true;
                        }
                    }
                    if ( j != 5 ) {
                        if ( input_line[ i ][ j + 1 ] == c ) {
                            starting_map.grids[ i ][ j ].slide = SLIDE_HORIZONTAL;
                            handled = true;
                        }
                    }
                }
                if ( !handled ) {
                    pr_info( "It should be handled %d:%d", i, j );
                }
            } else {
                starting_map.grids[ i ][ j ].which_block = ' ';
            }
        }
    }
}
