#pragma once

typedef enum {
    SLIDE_HORIZONTAL = 'h',
    SILDE_VERTICAL = 'v',
    SILDE_NONE = ' ',
} Slide;

// typedef enum {
//     EMPTY,
//     A,
//     B,
//     S, //Solution
// } BlockType;

typedef struct {
    Slide slide;
    char size;
    unsigned char which_block;
} Grid;

char grid_get_slide_char( const Grid &grid );
char grid_get_which_block( const Grid &grid );
char grid_get_which_size( const Grid &grid );