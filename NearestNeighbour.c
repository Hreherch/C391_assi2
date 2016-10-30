#include "NearestNeighbour.h"

// Populates the branchList (void *data) with information from the rtree node query
int display(void *data, int argc, char **argv, char **col_name) {
    int i = 0;
    node *branchList = (node*) data;
    char *result = strtok( argv[0], "{}\n" );
    
    // loop until no more nodes to pick up.
    while( 1 ) {
        if( result == NULL ) {
            break;
        }
        
        sscanf( result, "%ld %lf %lf %lf %lf", 
                &(branchList[i].id), &(branchList[i].minX), 
                &(branchList[i].maxX), &(branchList[i].minY), 
                &(branchList[i].maxY) );
        
        //printf( "%ld: %.15lf %.15lf %.15lf %.15lf\n", 
        //        branchList[i].id, 
       //         branchList[i].minX, branchList[i].maxX, 
        //        branchList[i].minY, branchList[i].maxY );
                
        i++;
        
        result = strtok( NULL, "{}\n" );
    }
    
    return 0;
}


void genBranchList( sqlite3 *db, point p, node parentNode, node *branchList ) {
    // TODO make this the general case of nodeno, use node.nodeno instaead of 1
    char *sql_str = "SELECT rtreenode(2, data) FROM projected_poi_node WHERE nodeno = %d;";
    char sqlStr_buffer[200] = {};
    
    sprintf(sqlStr_buffer, sql_str, parentNode.id );
    
    // execute the query 
    sqlite3_exec(db, sqlStr_buffer, display, branchList, NULL);
    //printf("%s\n", result_str);
    // Strtok the string 
} 

//void sortBranchList( /* branchList */ ) {
    
//}

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
    
    printf( "exploring node: %ld\n", currentNode.id );
    
    // get the objects or children node(s) of the currentNode
    genBranchList( db, p, currentNode, branchList );
    
    if ( branchList[0].id > 2000 ) {
        //printf( "Hit child node in %ld, returning\n", currentNode.id );
        return;
    }
    // Base case: leaf node, calculating distance to objects
    // IF node is leaf:
        // for child in Node:
            // dist = objectDist
            // if (dist < Nearest_dist ):
                //Nearest neighbour = object
                // nearestdsit = dist
                
    // Non-base case: not leaf node. (order, prune, then visit):
    // ELSE:
        // genBranchList( Point, Node, branchList )
        // sortBranchList( branchList )
        
        // prune DOWNWARD
        // last = pruneBranchList( Node, Point, Nearest, branchList )

        // Iterate through ABL:
        // For i = 1 to last:
            // newNode = get node from branch we want to explore
            
            // visit children nodes
        for( i = 0; i < 51; i++ ) {
            if( branchList[i].id == 0 ) {
                printf( "done exploring %ld's children\n", currentNode.id );
                break;
            }
            
            nearestNeighbourSearch( db, branchList[i], p, nearest, k );
            
        }
            
            // prune UPWARD
            // last = pruneBranchList( node, point, nearest, branchList )
           
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
    