#include "sqlite3.h"
#include <stdio.h>

#define DB_NAME "A2.db"

int main( int argc, char **argv ) {
    sqlite3 *db;
    char *sql_str;
    
    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)" );
        sqlite3_close( db );
        return( 1 );
    }
    
    
} //main 