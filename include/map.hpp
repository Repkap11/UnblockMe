#pragma once

#include "grid.hpp"
typedef union {
    Grid grids[ 6 ][ 6 ];
    unsigned char raw_data[ sizeof( Grid ) * 6 * 6 ];
} Map;

void map_print_slide( const Map &map );
void map_print_which_block( const Map &map );
void map_populate_from_chars( Map &map, const char * );