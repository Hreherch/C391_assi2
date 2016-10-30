#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H
#include "sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// MACRO DEFINITIONS
#define DB_NAME "A2.db"

// structs
typedef struct node node;
struct node {
    long id;
    double maxX;
    double minX;
    double maxY;
    double minY;
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
void genBranchList( sqlite3 *db, point p, node parentNode, node *branchList );

#endif 