#include "grid.hpp"
#include "logging.hpp"

char grid_get_slide_char( const Grid &grid ) {
    return grid.slide;
}

char grid_get_which_block( const Grid &grid ) {
    return grid.which_block;
}

char grid_get_which_size( const Grid &grid ) {
    return '0' + grid.size;
}