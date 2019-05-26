#include "map_hash_table.hpp"
#include "logging.hpp"
#include <string.h>

typedef int TableKey;

TableElement table[ MAP_SIZE ];
TableElement *tips;

unsigned int hash_function( const Map &map ) {
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

bool map_hash_table_add_map_if_unique( Table &table, const Map &map, const Map *parent ) {
    unsigned int hash = hash_function( map );
    // pr( "Hash:%u", hash );
    TableElement *element = &table.history[ hash ];
    while ( element != NULL && element->is_populated ) {
        if ( are_equal( element->map, map ) ) {
            return false;
        }
        element = element->next;
    }
    element->map = map;
    element->is_populated = true;
    element->next = new TableElement;
    element->parent = parent;
    return true;
}
