#include "map_hash_table.hpp"
#include "logging.hpp"

#define MAP_SIZE 100

unsigned int map_hash_table_hash( const Map &map ) {
    unsigned long hash = 5381;
    int c;

    for ( unsigned int i = 0; i < sizeof( Map ); i++ ) {
        unsigned long c = map.raw_data[ i ];
        hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */
    }
    return hash % MAP_SIZE;
}

void map_hash_table_add_map_if_unique( const Map &map ) {
    unsigned int hash = map_hash_table_hash( map );
    pr("Hash:%u", hash);
}