#include "grid.hpp"
#include "solve.hpp"

char grid_get_slide_char( const Grid &grid ) {
    if ( grid.which_block == ' ' ) {
        return ' ';
    } else {
        return grid.slide;
    }
}

char grid_get_which_block( const Grid &grid ) {
    return grid.which_block;
}