#pragma once
#include "map.hpp"

#define MAP_SIZE 100
typedef struct TableElement TableElement;
typedef struct TableElement {
    Map map;
    int is_populated;
    const Map *parent;
    TableElement *next;
} TableElement;

typedef struct {
    TableElement history[ MAP_SIZE ];
} Table;

bool map_hash_table_add_map_if_unique(Table& table, const Map &map, const Map *parent );