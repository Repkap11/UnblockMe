#include "map_hash_table.hpp"
#include "logging.hpp"
#include <string.h>

#define MAP_SIZE 100
typedef struct TableElement TableElement;
typedef struct TableElement {
    Map map;
    int is_populated;
    const Map *parent;
    TableElement* next;
} TableElement;

typedef int TableKey;

TableElement table[ MAP_SIZE ];

unsigned int map_hash_table_hash( const Map &map ) {
    unsigned long hash = 5381;
    int c;

    for ( unsigned int i = 0; i < sizeof( Map ); i++ ) {
        unsigned long c = map.raw_data[ i ];
        hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */
    }
    return hash % MAP_SIZE;
}

bool are_equal( const Map &first, const Map &second ) {
    return memcmp( first.raw_data, second.raw_data, sizeof( Grid ) ) == 0;
}

bool map_hash_table_add_map_if_unique( const Map &map ) {
    unsigned int hash = map_hash_table_hash( map );
    // pr( "Hash:%u", hash );
    TableElement *element = &table[ hash ];
    while ( element->is_populated ) {
        if ( are_equal( element->map, map ) ) {
            return false;
        }
        element = element->next;
    }
    element->map = map;
    element->is_populated = true;
    element->next = new TableElement;
    return true;
}
