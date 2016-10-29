// libraries
#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

// macros
#define DB_NAME "A2.db"
#define True 1
#define False 0

// structs
// struct Node {
//     long id;
//     int isLeaf;
//     double xMax;
//     double xMin;
//     double yMax;
//     double yMin;
//     Node *children[51];
// };

struct point {
    double x;
    double y;
};
// Global variables
// Node   *activeBranchList[1300];
// Node    global_nodeList[1300];
// int     global_nearest = 2000;
// long    bestObjectId = -1;

// nodeno, dataBlob
// void getNodeData( sqlite3_context *ctx, int argc, sqlite3_value **apArg ) {
//     char *zText = 0;
//   RtreeNode node;
//   Rtree tree;
//   int ii;

//   UNUSED_PARAMETER(nArg);
//   memset(&node, 0, sizeof(RtreeNode));
//   memset(&tree, 0, sizeof(Rtree));
//   tree.nDim = 2;
//   tree.nBytesPerCell = 8 + 8 * tree.nDim;
//   node.zData = (u8 *)sqlite3_value_blob(apArg[1]);
//   //printf("node.zData = %s\n", *node.zData);

//   for(ii=0; ii<NCELL(&node); ii++){
//     char zCell[512];
//     int nCell = 0;
//     RtreeCell cell;
//     int jj;

//     nodeGetCell(&tree, &node, ii, &cell);
//     sqlite3_snprintf(512-nCell,&zCell[nCell],"%lld", cell.iRowid);
//     // prints out the rowid
//     // printf("cell.iRowid = %lld\n", cell.iRowid);
//     nCell = (int)strlen(zCell);
//     for(jj=0; jj<tree.nDim*2; jj++){
//       sqlite3_snprintf(512-nCell,&zCell[nCell], " %g",
//                        (double)cell.aCoord[jj].f);
//       // prints out the coordinates of a mbr
//       // printf("cell.aCoord[jj].f = %g\n", cell.aCoord[jj].f);
//       nCell = (int)strlen(zCell);
//     }

//     if( zText ){
//       char *zTextNew = sqlite3_mprintf("%s {%s}", zText, zCell);
//       sqlite3_free(zText);
//       zText = zTextNew;
//     }else{
//       zText = sqlite3_mprintf("{%s}", zCell);
//     }
//   }

//   sqlite3_result_text(ctx, zText, -1, sqlite3_free);
//   // printf("HI");
//   // printf("node pparent = %d\n", node.pParent);
// }

// int display(void *data, int argc, char **argv, char **col_name) {
//     int i;
//     printf("%s", (char*)data);
//     for (i = 0; i < argc; i++) {
//         printf("%s = %s, ", col_name[i], argv[i] ? argv[i]: "NULL");
//     }
//     printf("\n");
//     return 0;
// }   

int main( int argc, char **argv ) {
    struct point search_point;
    sqlite3 *db;
    
    // Set all data in the nodeList to 0.
    // memset( global_nodeList, 0, sizeof(Node) * 1300)
    
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
    
    // sqlite3_create_function( db, "GETNODEDATA", 2, SQLITE_UTF8, NULL, getNodeData, NULL, NULL );

    char *sql_str = " SELECT rtreenode(nodeno, data) FROM projected_poi_node WHERE nodeno = 54;";
    sqlite3_exec( db, sql_str, NULL, NULL, NULL );
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