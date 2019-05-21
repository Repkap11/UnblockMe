#include "solve.hpp"
#include "map.hpp"
int main( ) {
    pr_info( "Hello World" );
    const char *input = "aaa...\n"
                        "bbb...\n"
                        "ccc...\n"
                        "def...\n"
                        "def...\n"
                        "def...";
    Map starting_map;
    map_populate_from_chars(starting_map, input);
    
    map_print_slide( starting_map );
    map_print_which_block( starting_map );
}