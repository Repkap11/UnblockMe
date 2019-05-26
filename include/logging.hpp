#pragma once

#include <stdio.h>
#define pr_info( fmt, ... ) fprintf( stdout, "%s:%d:%s():" fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__ );
#define pr( fmt, ... ) fprintf( stdout, fmt "\n", ##__VA_ARGS__ );