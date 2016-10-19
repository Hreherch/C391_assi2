#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

#define DB_NAME "A2.db"

int print_result( sqlite3_stmt *sql_stmt ) {

    while ( sqlite3_step( sql_stmt ) == SQLITE_ROW ) {
        printf( "%s\n", sqlite3_column_text( sql_stmt, 0 ) );
    }
}

int main( int argc, char **argv ) {
    sqlite3 *db;
    sqlite3_stmt *sql_stmt;
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

    sql_str = "DROP TABLE IF EXISTS bounded_by_rect;";

    sqlite3_exec(db, sql_str, NULL, NULL, NULL);
    
    sql_str = "CREATE TABLE bounded_by_rect AS \
                    SELECT  id \
                    FROM projected_poi ppoi\
                    WHERE minX >= ?\
                      AND maxY <= ?\
                      AND maxX <= ?\
                      AND minY >= ?;";
    
    if ( SQLITE_OK != sqlite3_prepare_v2( db, sql_str, -1, &sql_stmt,  0 ) ) {
        fprintf( stderr, "Preparation failed 1: %s\n", sqlite3_errmsg( db ) );
        sqlite3_close( db );
        return( 1 );
    } 

    int i = 1;
    for ( i = 1; i < 4; i++ ) {
        if ( SQLITE_OK != sqlite3_bind_double( sql_stmt, i, (double) atof(argv[i]) ) ) {
            fprintf( stderr, "Binding failed 1: %s\n", sqlite3_errmsg( db ) );
            sqlite3_close( db );
            return( 1 );
        }
    } // for

    sqlite3_step( sql_stmt );
    sqlite3_finalize( sql_stmt );

    // Query
    sql_str =  "SELECT pt.id \
                FROM bounded_by_rect bbr, poi_tag pt\
                WHERE bbr.id = pt.id\
                  AND key = 'class'\
                  AND value = ?;";

    if ( SQLITE_OK != sqlite3_prepare_v2( db, sql_str, -1, &sql_stmt,  0 ) ) {
        fprintf( stderr, "Preparation failed 1: %s\n", sqlite3_errmsg( db ) );
        sqlite3_close( db );
        return( 1 );
    } 

    if ( SQLITE_OK != sqlite3_bind_text( sql_stmt, 1, argv[5], -1, SQLITE_STATIC ) ) {
        fprintf( stderr, "Binding failed 2: %s\n", sqlite3_errmsg( db ) );
        sqlite3_close( db );
        return( 1 );
    }

    print_result( sql_stmt );
    
} //main 