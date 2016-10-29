
struct node {
    long id;
    int numChildren;
    long children[51];
}

// Returns the point's distance to an object (a rectangle)
double objectDist( /* Point, Object */ ) {
    
    return 0.0
}

// does a branch list thing
void genBranchList( /* Point, Node, branchlist */ ) {
    
}

void sortBranchList( /* branchList */ ) {
    
}

void pruneBranchList( /* Node, Point, Nearest, branchList */ ) {
    
}

void findNearestNeighbour( sqlite3 *db /* node, point, nearest, K */ ) {
    // Parameters
    /* current node, 
    search query, 
    nearest neighbor */
    
    // Local Variables
    /* Node newNode
     BRANCHARRAY branchList
     integer dist, last, i */
    
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
            // findNearestNeighbour( newNode, point, Nearest, K )
            
            // prune UPWARD
            // last = pruneBranchList( node, point, nearest, branchList )
           
}
    