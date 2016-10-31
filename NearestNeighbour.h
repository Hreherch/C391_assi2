#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H
#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// MACRO DEFINITIONS
#define DB_NAME "A2.db"

#define DOWNWARD_PRUNE 420
#define UPWARD_PRUNE 469

// structs

// We call this a "node" but in our program it represents both a node and an object.
typedef struct node node;
struct node {
    long id;
    double maxX;
    double minX;
    double maxY;
    double minY;
    
    double minDist;
    double minmaxDist;
};

typedef struct nearestN {
    long id;
    double distance;
} nearestN;

typedef struct point point;
struct point {
    double x;
    double y;
};

// No.
int display(void *data, int argc, char **argv, char **col_name);

// No
int genBranchList( sqlite3 *db, point p, node parentNode, node *branchList );

#endif 