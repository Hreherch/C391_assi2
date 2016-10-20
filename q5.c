#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DB_NAME "A2.db"

void makeCartesianIndex( sqlite3 *db ) {
    char *sql_str = "DROP TABLE IF EXISTS projected_poI_regTable;\
                     DROP INDEX IF EXISTS poi_index;\
                     CREATE TABLE projected_poi_regTable AS\
                        SELECT id,\
                            (lat - 48.06) * (1000/.189) as minX, \
                            ((lat - 48.06 + (10/111191)) * (1000/.189)) as maxX,\
                            (lon - 11.358) * (1000/.366) as minY, \
                            ((lon - 11.358 + (10/74539)) * (1000/.366)) as maxY\
                        FROM poi;\
                     CREATE INDEX poi_index ON\
                        projected_poi_regTable( minX, maxX, minY, maxY );";

    sqlite3_exec( db, sql_str, NULL, NULL, NULL );
}

double rTree_test( sqlite3 *db, int minX, int maxX, int maxY, int minY ) {
    clock_t start, end;
    char sql_buffer[1000] = {};
    char *sql_str;
    
    sql_str = "CREATE TABLE bounded_by_rect AS \
                    SELECT  id \
                    FROM projected_poi ppoi\
                    WHERE minX >= %d\
                      AND maxY <= %d\
                      AND maxX <= %d\
                      AND minY >= %d;";
    
    sprintf( sql_buffer, sql_str, minX, maxY, maxX, minY );

    start = clock();
    sqlite3_exec( db, sql_buffer, NULL, NULL, NULL );
    end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC;
}

double index_test( sqlite3 *db, int minX, int maxX, int maxY, int minY ) {
    clock_t start, end;
    char sql_buffer[1000] = {};
    char *sql_str;

    sql_str = "SELECT * \
               FROM projected_poi_regTable \
               WHERE minX >= %d \
                 AND maxX <= %d \
                 AND minY >= %d \
                 AND maxY <= %d;";

    sprintf( sql_buffer, sql_str, minX, maxX, minY, maxY );

    start = clock();
    sqlite3_exec( db, sql_buffer, NULL, NULL, NULL );
    end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC;
}

int main( int argc, char **argv ) {
    sqlite3 *db;
    //sqlite3_stmt *sql_stmt;
    char *sql_str;
    int random_dim = rand() % 1001;
    int length = 0;
    srand(time(NULL));

    if ( argc != 2 ) {
        fprintf( stderr, "Usage: ./q5 side_length\n" );
        return( 1 );
    }

    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)" );
        sqlite3_close( db );
        return( 1 );
    }

    makeCartesianIndex( db );

    length = atoi( argv[1] );

    int i = 0;
    int j = 0;
    double rTree_totalime = 0;
    double index_totalTime = 0;
    for ( i = 0; i < 100; i++ ) {
        double rTree_timeForSquare = 0;
        double index_timeForSquare = 0;   
        
        // make a square
        int minX = rand() % (1001 - length);
        int minY = rand() % (1001 - length);
        int maxX = minX + length;
        int maxY = minY + length;

        for ( j = 0; j < 20; j++ ) {
            rTree_timeForSquare += rTree_test( db, minX, maxX, maxY, minY );

            index_timeForSquare += index_test( db, minX, maxX, maxY, minY );
        } // 20 times for square loop

        rTree_totalime += (rTree_timeForSquare/20);
        index_totalTime += (index_timeForSquare/20);
        

    } // 100 square for loop 
    
    double rTreeAvgTime = rTree_totalime / 100;
    double indexAvgTime = index_totalTime / 100;

    //printf( "%lf, %lf\n", rTreeAvgTime, indexAvgTime );

    printf( "\nParameter l: %d\n\n", length);
    printf( "Average runtime with r-tree: %lfms\n\n", rTreeAvgTime*1000 );
    printf( "Average runtime without r-tree: %lfms\n\n", indexAvgTime*1000 );

    sqlite3_close( db );

    return( 0 );
}