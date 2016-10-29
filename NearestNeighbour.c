#include "NearestNeighbour.h"

// Returns the point's distance to an object (a rectangle)
//double objectDist( /* Point, Object */ ) {
    
    //return 0.0
//}
int display(void *data, int argc, char **argv, char **col_name) {
     int i;
     printf("%s", (char*)data);
     for (i = 0; i < argc; i++) {
         printf("%s = %s", col_name[i], argv[i] ? argv[i]: "NULL");
     }
     printf("\n");
     return 0;
}
// does a branch list thing
void genBranchList( point search_point, node node ) {
    // TODO make this the general case of nodeno, use node.nodeno instaead of 1
    char *sql_str = "SELECT rtreenode(2, data) FROM projected_poi_node WHERE nodeno = 1;";
    char result_str[10000];
    memset(result_str, 0, sizeof(result_str));

    // execute the query 
    sqlite3_exec(db, sql_str, NULL, NULL, NULL);
    printf("%s\n", result_str);
    // Strtok the string 
}

//void sortBranchList( /* branchList */ ) {
    
//}

//void pruneBranchList( /* Node, Point, Nearest, branchList */ ) {
    
//}

//void findNearestNeighbour( sqlite3 *db /* node, point, nearest, K */ ) {
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
           
//}
    