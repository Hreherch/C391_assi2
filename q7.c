// INCLUDE STATEMENTS
#include "NearestNeighbour.h"

// global pointer to the database
int main( int argc, char **argv ) {
    struct point search_point;

    if ( argc != 3 ) {
        fprintf( stderr, "usage: ./q7 x1 y1\n" );
        return( 1 );
    }

    search_point.x = atof(argv[1]);
    search_point.y = atof(argv[2]);

    
    findNearestNeighbour( search_point, 1 );
    
    return( 0 );
}