#include "sqlite3.h"
#include <string.h>
#include <math.h>

struct point {
    double x ;
    double y;
};

int main( int argc, char **argv ) {
    struct point search_point;
    sqlite3 *db;
    //sqlite3_stmt *sql_stmt;
    char *sql_str;

    if ( argc != 3 ) {
        fprintf( stderr, "usage: ./q7 x1 y1" );
        return( 1 );
    }

    search_point.x = atof(argv[1]);
    search_point.y = atof(argv[2]);

    
    
    
}

// Do we need to find the distance between two points or a point and a rectangle?
double euclidean_distance( point search, point found ) {
    double dx = 0;
    double dy = 0;
    double dist = 0;

    dx = ( search.x - found.x );
    dy = ( search.y - found.y );
    
    // using the center of a rectangle as found 
    // dx = max(abs(search.x - found.x) - 10 / 2, 0);
    // dy = max(abs(search.y - found.y) - 10 / 2, 0);

    dist = dx * dx + dy * dy;
    return dist;
}