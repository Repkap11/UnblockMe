#pragma once
#include "map.hpp"
#include "move_command.hpp"

#define MAP_SIZE 1000
typedef struct TableElement TableElement;
typedef struct TableElement {
    Map map;
    TableElement *parent;
    TableElement *next;
    MoveCommand move;
    TableElement( ) : parent( 0 ), next( 0 ) {
    }
    TableElement( const MoveCommand &move ) : parent( 0 ), next( 0 ), move( move ) {
    }

} TableElement;

typedef struct {
    TableElement history[ MAP_SIZE ];
} Table;

bool map_hash_table_add_map_if_unique( Table &table, const Map &map, const MoveCommand &move, const Map *parent );
void map_hash_table_print_solution( Table &table, const Map &map );
