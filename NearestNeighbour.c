#include "NearestNeighbour.h"

// quicksort function to sort branchList
int compareFunct( const void *a, const void *b ) {
    double temp = (((node*)a)->minDist - ((node*)b)->minDist);
    if ( temp < 0 ) { return -1; }
    else if ( temp > 0 ) { return 1; }
    else { return 0; }
}

// calculates minmaxdist for a node and puts the information inside the node.
void minmaxDist( node *aNode, point p ) {
    // Do not need to worry about summation, as n=2. There is only two eqns to calculate,
    // iteratively selecting them would have taken the same amount of work. 
    
    double rect_centerX = (aNode->minX + aNode->maxX) / 2;
    double rect_centerY = (aNode->minY + aNode->maxY) / 2;
    
    // calculate rm_i and rM_k, etc... 
    double rmx = (p.x <= rect_centerX) ? aNode->minX : aNode->maxX;
    double rMx = (p.x >= rect_centerX) ? aNode->minX : aNode->maxX;
    double rmy = (p.y <= rect_centerY) ? aNode->minY : aNode->maxY;
    double rMy = (p.y >= rect_centerY) ? aNode->minY : aNode->maxY;
    
    double term_1 = (p.x - rmx);
    double term_2 = (p.y - rMy);
    double minmaxdist_1 = (term_1 * term_1) + (term_2 * term_2);
    
    term_1 = (p.y - rmy);
    term_2 = (p.x - rMx);
    double minmaxdist_2 = (term_1 * term_1) + (term_2 * term_2);
    
    // set the one that's smaller to be minmaxdist
    aNode->minmaxDist = (minmaxdist_1 < minmaxdist_2) ? minmaxdist_1 : minmaxdist_2;
}

// calculates mindist (which is also the mindist between any rectangle and a point)
// for either a node or a object (which uses the same type as node)
void mindist( node *aNode, point p ) {
    double mindist = 0;
    int i;
    double rx = p.x;
    double ry = p.y;
    
    // see r_i definition for mindist
    if ( p.x < aNode->minX ) { rx = aNode->minX; }
    else if ( p.x > aNode->maxX ) { rx = aNode->maxX; }
    
    if ( p.y < aNode->minY ) { ry = aNode->minY; }
    else if ( p.y > aNode->maxY ) { ry = aNode->maxY; }
    
    double sum1 = (p.x - rx); 
    double sum2 = (p.y - ry);
    
    printf( "rect %ld: %lf %lf %lf %lf\n", aNode->id, aNode->minX, aNode->maxX, aNode->minY, aNode->maxY );
    printf( "point x=%lf, y=%lf\n", p.x, p.y );
   
    aNode->minDist = (sum1 * sum1) + (sum2 * sum2);
    printf( "mindist=%lf\n", aNode->minDist );
}


// Populates the branchList (void *data) with information from the rtree node query
int callback(void *data, int argc, char **argv, char **col_name) {
    int i = 0;
    node *branchList = (node*) data;
    char *result = strtok( argv[0], "{}\n" );
    point p = {};
    
    // This is a hacky part. We hid the query point inside branchList so that we 
    // could calulate it while running this query.
    p.x = branchList[0].minDist;
    p.y = branchList[0].minmaxDist;
    
    // loop until no more nodes to pick up.
    while( 1 ) {
        if( result == NULL ) {
            break;
        }
        
        sscanf( result, "%ld %lf %lf %lf %lf", 
                &(branchList[i].id), &(branchList[i].minX), 
                &(branchList[i].maxX), &(branchList[i].minY), 
                &(branchList[i].maxY) );
        
        // on objects we only calculate mindist, so skip the calculation of minmaxdist
        // (because this equals the distance to the rectangle)
        if ( branchList[i].id > 2000 ) {
            minmaxDist( &(branchList[i]), p );
        }
        mindist( &(branchList[i]), p );
        
        
        i++;
        
        result = strtok( NULL, "{}\n" );
    }
    
    return 0;
}


int genBranchList( sqlite3 *db, point p, node parentNode, node *branchList ) {
    // TODO make this the general case of nodeno, use node.nodeno instaead of 1
    char *sql_str = "SELECT rtreenode(2, data) FROM projected_poi_node WHERE nodeno = %d;";
    char sqlStr_buffer[200] = {};
    int i;
    
    sprintf(sqlStr_buffer, sql_str, parentNode.id );
    
    // execute the query 
    sqlite3_exec(db, sqlStr_buffer, callback, branchList, NULL);
    
    // return the number of nodes generated
    for ( i = 0; i < 51; i++ ) {
        if( branchList[i].id == 0 ) {
            return i;
        }
    }
    // b/c branchList[50].id may not be 0 => there are 51 elements. (i+1 = 51 here)
    return i + 1;
} 

void sortBranchList( node *branchList ) {
    
}

//void pruneBranchList( /* Node, Point, Nearest, branchList */ ) {
    
//}

void nearestNeighbourSearch( sqlite3 *db,       /* The database for the R-Tree */
                           node currentNode,    /* The current node being explored */
                           point p,             /* The point being queried */
                           nearestN **nearest,  /* The current nearestNeighbour Object */
                           int k ) {            /* The number of nearest neighbours we want */
    
    // Local Variables
    node newNode = {};          
    node branchList[51] = {};
    int dist = 0; 
    int last = 0; 
    int i = 0;
    
    /*
     * This is really hacky (sorry). We're going to calculate the mindist and 
     * minmaxdist while we run the SQL query, please see the callback function.
     */
    branchList[0].minDist = p.x;
    branchList[0].minmaxDist = p.y;
    
    printf( "exploring node: %ld\n", currentNode.id );
    
    // get the objects or children node(s) of the currentNode
    last = genBranchList( db, p, currentNode, branchList );
    
    if ( branchList[0].id > 2000 ) { // base case: in leaf node
        //printf( "Hit child node in %ld, returning\n", currentNode.id );
        // for child in Node:
            // dist = objectDist
            // if (dist < Nearest_dist ):
                //Nearest neighbour = object
                // nearestdsit = dist
        return;
      
    }
    else { // Non-base case: not leaf node. (order, prune, then visit)
        qsort( branchList, last, sizeof( node ), compareFunct );
        
        // prune DOWNWARD
        // last = pruneBranchList( Node, Point, Nearest, branchList )
            
        // visit children nodes in branchList
        for( i = 0; i < 51; i++ ) {
            // Skip element b/c id==0 means to skip (or that the node doesn't exist)
            if( branchList[i].id == 0 ) {
                printf( "done exploring %ld's children\n", currentNode.id );
                continue;
            }
            
            printf( "%ld: mindist: %lf\n", branchList[i].id, branchList[i].minDist );
            
            nearestNeighbourSearch( db, branchList[i], p, nearest, k );
        
            // prune UPWARD
            // last = pruneBranchList( node, point, nearest, branchList )
        } // For (children in currentNode)
    }
}

void findNearestNeighbour( point query_point, int k ) {
    node rootNode = {};
    sqlite3 *db;
    nearestN **nearest;
    int i;
    
    // allocate memory to keep track of k nearest neighbours
    nearest = calloc( k, sizeof(nearestN*) );
    for( i = 0; i < k; i++ ) {
        nearest[i] = calloc( 1, sizeof(nearestN) );
        nearest[i]->id = -1;
        nearest[i]->distance = 100000;
    }
    
    // init parent node, don't really need this but y'know why not
    rootNode.id = 1;
    rootNode.minX = 0; rootNode.maxX = 1000; 
    rootNode.minY = 0; rootNode.maxY = 1000;
    
    // open the DB connection
    if( 0 != sqlite3_open( DB_NAME, &db ) ) {
        fprintf( stderr, "Failed to open DB(is DB in folder?)\n" );
        sqlite3_close( db );
        exit( -1 );
    }
    
    // begin the recursive alg
    nearestNeighbourSearch( db, rootNode, query_point, nearest, k );
    
    // TODO need to do something here to report k nearest...
    
    // free the memory used to store the k nearest neighbours
    for( i = 0; i < k; i++ ) {
        free( nearest[i] );
    }
    free( nearest );
}
    