#ifndef TREE_H
#define TREE_H

#include "clubs.h"

typedef sClub sItem;

typedef struct node
{
    sItem         item;
    int           node_count;
    struct node * node_left;
    struct node * node_right;
} * sNode;

typedef struct tree
{
    sNode   tree_root;
    int     tree_count;
    sNode * active_node_ptr;

    int     scan_type;
    int  (* cmp_nodes  )();

    bool (* create     )();
    int  (* scan       )();
    int  (* scan_nodes )();
    sNode(* create_node)();
    sNode(* add_node   )();
    void (* delete_tree)();

} * sTree;

typedef enum SCAN_TYPES
{
    RT_L_R
   ,L_RT_R
   ,L_R_RT
   ,SCAN_TYPES_END
} eSCAN_TYPES;

bool  tre_init        (sTree *);
bool  tre_set_current (sTree);
sNode tre_create_node (sItem);

#endif // TREE_H
