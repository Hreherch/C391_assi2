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

double rTree_test( sqlite3 *db, double minX, double maxX, double maxY, double minY ) {
    clock_t start, end;
    char sql_buffer[1000] = {};
    char *sql_str;
    
    sql_str = "CREATE TABLE bounded_by_rect AS \
                    SELECT  id \
                    FROM projected_poi ppoi\
                    WHERE minX >= %lf\
                      AND maxY <= %lf\
                      AND maxX <= %lf\
                      AND minY >= %lf;";
    
    sprintf( sql_buffer, sql_str, minX, maxY, maxX, minY );

    start = clock();
    sqlite3_exec( db, sql_buffer, NULL, NULL, NULL );
    end = clock();

    return (double) (end - start) / CLOCKS_PER_SEC;
}

void makeSquares( double **squares, double length ) {
    int i = 0;
    for (i = 0; i < 100; i++ ) {
        squares[i] = malloc( sizeof(double) * 4 );
        double maxX = 1000;
        double maxY = 1000;
        double minX = 0;
        double minY = 0;
        int modLength = (int) length;
        if (length != 1000) {
            minX = (rand() % (1000 * 100) - (modLength * 100) ) / 100;
            minY = (rand() % (1000 * 100) - (modLength * 100) ) / 100;
            maxX = minX + length;
            maxY = minY + length;
        }
        squares[i][0] = minX;
        squares[i][1] = maxX;
        squares[i][2] = minY;
        squares[i][3] = maxY;
        //printf( "made sqr: \n\tminX:%lf\n\tmaxX:%lf\n\tminY%lf\n\tmaxY:%lf\n", minX, maxX, minY, maxY );
    }
}

void freeSquares( double **squares ) {
    int i = 0;
    for ( i = 0; i < 100; i++ ) {
        free( squares[i] );
    }
}

double index_test( sqlite3 *db, double minX, double maxX, double maxY, double minY ) {
    clock_t start, end;
    char sql_buffer[1000] = {};
    char *sql_str;

    sql_str = "SELECT * \
               FROM projected_poi_regTable \
               WHERE minX >= %lf \
                 AND maxX <= %lf \
                 AND minY >= %lf \
                 AND maxY <= %lf;";

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
    double length = 0;
    srand(time(NULL));

    if ( argc != 2 ) {
        fprintf( stderr, "Usage: ./q5 side_length\n" );
        return( 1 );
    }

    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)\n" );
        sqlite3_close( db );
        return( 1 );
    }

    makeCartesianIndex( db );

    length = atof( argv[1] );
    
    if (length > 1000 || length <= 0) {
        fprintf( stderr, "0 < side_length <= 1000\n" );
        sqlite3_close( db );
        return( 1 );
    }
    
    double *squares[100];
    double rTree_squareTime[100] = {};
    double index_squareTime[100] = {};
    
    makeSquares( squares, length );

    int i = 0;
    int j = 0;
    double rTree_totalime = 0;
    double index_totalTime = 0;
    for ( i = 0; i < 20; i++ ) {


        for ( j = 0; j < 100; j++ ) {
            double minX = squares[j][0];
            double maxX = squares[j][1];
            double minY = squares[j][2];
            double maxY = squares[j][3];
            //printf( "testing: %lf", minY );
            rTree_squareTime[j] += rTree_test( db, minX, maxX, maxY, minY );

            index_squareTime[j] += index_test( db, minX, maxX, maxY, minY );
        } // iterate over 100 squares
      
    } // do 100 iterations 20 times
    
    double rTreeAvgTime = 0;
    double indexAvgTime = 0;
    
    for ( i = 0; i < 100; i++ ) {
        rTreeAvgTime += rTree_squareTime[i]/20;
        indexAvgTime += index_squareTime[i]/20;
    }
    
    rTreeAvgTime /= 100;
    indexAvgTime /= 100;
    
    freeSquares( squares );

    //printf( "%lf, %lf\n", rTreeAvgTime, indexAvgTime );

    printf( "\nParameter l: %lf\n\n", length);
    printf( "Average runtime with r-tree: %lfms\n\n", rTreeAvgTime*1000 );
    printf( "Average runtime without r-tree: %lfms\n\n", indexAvgTime*1000 );

    sqlite3_close( db );

    return( 0 );
}