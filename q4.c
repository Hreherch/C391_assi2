#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_NAME "A2.db"

int main( int argc, char **argv ) {
    sqlite3 *db;
    char *sql_str;
    
    if ( argc != 6 ) {
        fprintf( stderr, "Usage: ./q4 minX maxY maxX minY classC" );
        return( 1 );
    }

    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)" );
        sqlite3_close( db );
        return( 1 );
    }
    

    
} //main 