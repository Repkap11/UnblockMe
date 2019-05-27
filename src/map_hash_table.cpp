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
    bool result = memcmp( first.raw_data, second.raw_data, sizeof( Map ) ) == 0;
    return result;
}

bool map_hash_table_add_map_if_unique( Table &table, const Map &map, const Map *parent ) {

    // if ( parent != NULL && are_equal( map, *parent ) ) {
    //     pr_info( "A map and its parent should be the same" );
    // }

    unsigned int hash = hash_function( map );
    // pr( "Hash:%u", hash );
    TableElement *element = &table.history[ hash ];
    if ( element == NULL ) {
        pr_info( "Why is element null" );
    }
    while ( element->next != NULL ) {
        if ( are_equal( element->map, map ) ) {
            return false;
        }
        element = element->next;
    }
    element->map = map;
    element->next = new TableElement;

    if ( parent != NULL ) {
        Map parentMap = *parent;
        unsigned int hash = hash_function( parentMap );
        TableElement *parentElement = &table.history[ hash ];
        bool found_parent = false;
        while ( parentElement != NULL ) {
            if ( are_equal( parentElement->map, parentMap ) ) {
                element->parent = parentElement;
                if ( element == element->parent ) {
                    pr_info( "An element's parent shouldn't be itself" );
                }
                return true;
            }
            parentElement = parentElement->next;
        }
        pr_info( "Should have found a parent" );
    } else {
        element->parent = NULL;
    }
    if ( element == element->parent ) {
        pr_info( "An element's parent shouldn't be itself" );
    }
    return true;
}

void map_hash_table_print_solution( Table &table, const Map &input_map ) {
    Map map_temp = input_map;
    Map &map = map_temp;
    unsigned int hash = hash_function( map );
    TableElement *element = &table.history[ hash ];
    while ( element != NULL ) {
        if ( are_equal( element->map, map ) ) {
            break;
        } else {
            element = element->next;
        }
    }
    int length = 1;
    while ( element != NULL ) {
        length++;
        map_print_which_block( element->map );
        element = element->parent;
    }
    pr( "Solution Length:%d", length );
}
