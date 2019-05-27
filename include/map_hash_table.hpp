#pragma once
#include "map.hpp"

#define MAP_SIZE 10000
typedef struct TableElement TableElement;
typedef struct TableElement {
    Map map;
    TableElement *parent;
    TableElement *next;
    TableElement( ) : parent( 0 ), next( 0 ) {
    }

} TableElement;

typedef struct {
    TableElement history[ MAP_SIZE ];
} Table;

bool map_hash_table_add_map_if_unique( Table &table, const Map &map, const Map *parent );
void map_hash_table_print_solution( Table &table, const Map &map );
