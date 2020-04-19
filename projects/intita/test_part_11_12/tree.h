#ifndef TREE_H
#define TREE_H

#include "clubs.h"

typedef sClub sItem;

typedef struct node
{
    sItem         item;
    struct node * node_left;
    struct node * node_right;
} * sNode;

typedef struct tree
{
    sNode   tree_root;
    int     tree_count;

    int     scan_type;
    bool (* create)    ();
    int  (* scan      )();
    int  (* scan_nodes)();
} * sTree;

typedef enum SCAN_TYPES
{
    RT_L_R
   ,L_RT_R
   ,L_R_RT
   ,SCAN_TYPES_END
} eSCAN_TYPES;

bool tre_init        (sTree *);
bool tre_set_current (sTree);
void tre_delete      ();

#endif // TREE_H
