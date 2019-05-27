#include "map.hpp"
#include "grid.hpp"
#include "logging.hpp"

void map_print_slide( const Map &map ) {
    // pr( "--Slide-" );
    pr( "┌──────┐" );
    for ( int i = 0; i < 6; i++ ) {
        const Grid *line = map.grids[ i ];
        const char *end_char = i == 2 ? " " : "│";
        pr( "│%c%c%c%c%c%c%s", grid_get_slide_char( line[ 0 ] ), grid_get_slide_char( line[ 1 ] ), grid_get_slide_char( line[ 2 ] ), grid_get_slide_char( line[ 3 ] ), grid_get_slide_char( line[ 4 ] ), grid_get_slide_char( line[ 5 ] ),
            end_char );
    }
    pr( "└──────┘" );
    pr( "" );
}

void map_print_which_block( const Map &map ) {
    // pr( "--Block-" );
    pr( "┌──────┐" );
    for ( int i = 0; i < 6; i++ ) {
        const Grid *line = map.grids[ i ];
        const char *end_char = i == 2 ? " " : "│";
        pr( "│%c%c%c%c%c%c%s", grid_get_which_block( line[ 0 ] ), grid_get_which_block( line[ 1 ] ), grid_get_which_block( line[ 2 ] ), grid_get_which_block( line[ 3 ] ), grid_get_which_block( line[ 4 ] ), grid_get_which_block( line[ 5 ] ),
            end_char );
    }
    pr( "└──────┘" );
    pr( "" );
}

void map_print_size( const Map &map ) {
    // pr( "--Size--" );
    pr( "┌──────┐" );
    for ( int i = 0; i < 6; i++ ) {
        const Grid *line = map.grids[ i ];
        const char *end_char = i == 2 ? " " : "│";
        pr( "│%c%c%c%c%c%c%s", grid_get_which_size( line[ 0 ] ), grid_get_which_size( line[ 1 ] ), grid_get_which_size( line[ 2 ] ), grid_get_which_size( line[ 3 ] ), grid_get_which_size( line[ 4 ] ), grid_get_which_size( line[ 5 ] ),
            end_char );
    }
    pr( "└──────┘" );
    pr( "" );
}

void map_populate_from_chars( Map &starting_map, const char *input ) {
    char input_line[ 6 ][ 6 ];
    sscanf( input, "%6s\n%6s\n%6s\n%6s\n%6s\n%6s", input_line[ 0 ], input_line[ 1 ], input_line[ 2 ], input_line[ 3 ], input_line[ 4 ], input_line[ 5 ] );

    for ( int i = 0; i < 6; i++ ) {
        for ( int j = 0; j < 6; j++ ) {
            char c = input_line[ i ][ j ];
            Grid *grid = &starting_map.grids[ i ][ j ];
            if ( c != '.' ) {
                grid->which_block = c;
                bool handled = false;

                if ( i != 0 ) {
                    if ( input_line[ i - 1 ][ j ] == c ) {
                        Grid *near_grid = &starting_map.grids[ i - 1 ][ j ];
                        // This is an extention of the grid above
                        grid->slide = near_grid->slide;
                        char new_size = near_grid->size + 1;
                        for ( int a = 0; a < new_size; a++ ) {
                            starting_map.grids[ i - a ][ j ].size = new_size;
                        }
                        handled = true;
                    }
                }
                if ( j != 0 ) {
                    if ( input_line[ i ][ j - 1 ] == c ) {
                        Grid *near_grid = &starting_map.grids[ i ][ j - 1 ];
                        // This is an extention of the grid to the left
                        grid->slide = near_grid->slide;
                        char new_size = near_grid->size + 1;
                        for ( int a = 0; a < new_size; a++ ) {
                            starting_map.grids[ i ][ j - a ].size = new_size;
                        }
                        handled = true;
                    }
                }
                if ( !handled ) {
                    if ( i != 5 ) {
                        if ( input_line[ i + 1 ][ j ] == c ) {
                            grid->slide = SILDE_VERTICAL;
                            grid->size = 1;
                            handled = true;
                        }
                    }
                    if ( j != 5 ) {
                        if ( input_line[ i ][ j + 1 ] == c ) {
                            grid->slide = SLIDE_HORIZONTAL;
                            grid->size = 1;
                            handled = true;
                        }
                    }
                }
                if ( !handled ) {
                    pr_info( "It should be handled %d:%d", i, j );
                }
            } else {
                grid->which_block = ' ';
                grid->slide = SILDE_NONE;
                grid->size = 0;
            }
        }
    }
}
