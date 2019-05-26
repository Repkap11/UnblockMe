#include "logging.hpp"
#include "map.hpp"
#include "map_hash_table.hpp"

void extend_tip( Table &table );
void add_successors( Table &table, const Map &map );
bool is_solution( const Map &map );

TableElement *tip;

int main( ) {
    pr_info( "Hello World" );
    const char *input = "aaa...\n"
                        "bbb...\n"
                        "ccc...\n"
                        "def...\n"
                        "def...\n"
                        "def...";
    Map starting_map;
    map_populate_from_chars( starting_map, input );

    // map_print_slide( starting_map );
    map_print_which_block( starting_map );
    Table table;
    map_hash_table_add_map_if_unique( table, starting_map, NULL );
    tip = new TableElement;
    tip->map = starting_map;
    tip->parent = NULL;
    tip->is_populated = true;
    tip->next = new TableElement;
    extend_tip( table );
    if ( is_solution( tip->map ) ) {
        pr( "Found Solution" );
        // map_print_which_block( tip->map );
        map_hash_table_print_solution( table, tip->map );
    } else {
        pr( "Ran out of tips without finding a solution" );
    }
    // TODO free all the tips...
}

bool is_solution( const Map &map ) {
    return true;
}

void extend_tip( Table &table ) {
    TableElement *element = tip;
    while ( element->is_populated ) { // While the tip isn't the last tip.
        if ( is_solution( element->map ) ) {
            break;
        }
        add_successors( table, element->map );
        TableElement *old_element = element;
        element = element->next;
        delete old_element;
    }
}

void add_successors( Table &table, const Map &map ) {
    TableElement *element = new TableElement;
    element->map = map;

    bool was_added = map_hash_table_add_map_if_unique( table, element->map, &map );
    if ( was_added ) {
        tip->next = element;
        tip->is_populated = true;
        tip = element;
    } else {
        delete element;
    }
}