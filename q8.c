// INCLUDE STATEMENTS
#include "NearestNeighbour.h"

// global pointer to the database
int main( int argc, char **argv ) {
    struct point search_point;

    if ( argc != 4 ) {
        fprintf( stderr, "usage: ./q8 x1 y1 k\n" );
        return( 1 );
    }

    search_point.x = atof(argv[1]);
    search_point.y = atof(argv[2]);

    int k = atoi( argv[3] );
    
    if ( k <= 0 ) {
        fprintf( stderr, "k must be an integer larger than 0.\n");
        return( 1 );
    }
    
    findNearestNeighbour( search_point, k );
    
    return( 0 );
}