#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define DB_NAME "A2.db"

int main( int argc, char **argv ) {
    struct point search_point;
    sqlite3 *db;
    //sqlite3_stmt *sql_stmt;
    // char *sql_str;

    if ( argc != 4 ) {
        fprintf( stderr, "usage: ./q8 x1 y1 k\n" );
        return( 1 );
    }

    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)\n" );
        sqlite3_close( db );
        return( 1 );
    }

    return 0;
}