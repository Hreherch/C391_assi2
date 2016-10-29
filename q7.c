#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <math.h>


#define DB_NAME "A2.db"

struct point {
    double x ;
    double y;
};

int display(void *data, int argc, char **argv, char **col_name) {
    int i;
    printf("%s", (char*)data);
    for (i = 0; i < argc; i++) {
        printf("%s = %s, ", col_name[i], argv[i] ? argv[i]: "NULL");
    }
    printf("\n");
    return 0;
}

int main( int argc, char **argv ) {
    struct point search_point;
    sqlite3 *db;
    //sqlite3_stmt *sql_stmt;
    // char *sql_str;

    if ( argc != 3 ) {
        fprintf( stderr, "usage: ./q7 x1 y1\n" );
        return( 1 );
    }

    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)\n" );
        sqlite3_close( db );
        return( 1 );
    }

    char *sql_str = " SELECT rtreenode(2, data) FROM projected_poi_node WHERE nodeno = 54;";
    sqlite3_exec( db, sql_str, display, NULL, NULL );
    search_point.x = atof(argv[1]);
    search_point.y = atof(argv[2]);

    return 0;
}

// // Do we need to find the distance between two points or a point and a rectangle?
// double euclidean_distance( point search, point found ) {
//     double dx = 0;
//     double dy = 0;
//     double dist = 0;

//     dx = ( search.x - found.x );
//     dy = ( search.y - found.y );
    
//     // using the center of a rectangle as found 
//     // dx = max(abs(search.x - found.x) - 10 / 2, 0);
//     // dy = max(abs(search.y - found.y) - 10 / 2, 0);

//     dist = dx * dx + dy * dy;
//     return dist;
// }