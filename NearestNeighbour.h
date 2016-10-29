

#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H
#include "sqlite3.h"
#include <string.h>
#include <stdio.h>

// structs
typedef struct node node;
struct node {
    long nodeno;
    int numChildren;
    long children[51];
};

struct dimensions {
    double x1;
    double x2;
    double y1;
    double y2;
};

typedef struct point point;
struct point {
    double x;
    double y;
};

// the global active branch list 
extern struct node active_branch_list[51];
extern sqlite3 *db;
int display(void *data, int argc, char **argv, char **col_name);
void genBranchList(point search_point, node node);

#endif 