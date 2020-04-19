#include "clubs.h"
#include "tree.h"
//----------------------------------------------------------
static sTree _TREE_CURRENT;
//----------------------------------------------------------
static sNode tre_create_nodes(sItem, int);
static int   tre_erase_node  (sNode *);
//----------------------------------------------------------
typedef int (*handle_node)();
static bool  tre_create      (sItem, int);
static int   tre_scan        (handle_node);
static int   tre_scan_nodes  (sNode *, int, int *, handle_node);
//----------------------------------------------------------
bool tre_init(sTree * ptr_tree)
{
    sTree tree = NULL;

    tree = (sTree)malloc(sizeof(struct tree));

    if( tree == NULL ) return false;

    _TREE_CURRENT    = tree;

    tree->tree_root = NULL;
    tree->tree_count = 0;

    tree->scan_type  = 0; // 0: _Root_LeftRight ||
                          // 1: Left_Root_Right ||
                          // 2: LeftRight_Root_ ||
    tree->create     = tre_create;
    tree->scan       = tre_scan;
    tree->scan_nodes = tre_scan_nodes;


    *ptr_tree = tree;

    return true;
}

bool tre_set_current (sTree tree)
{
    _TREE_CURRENT = tree;
    return true;
}

bool tre_create(sItem items, int items_count)
{
    sTree tree = _TREE_CURRENT;
    tree->tree_root = tre_create_nodes(items, items_count);
    return true;
}

sNode tre_create_nodes(sItem items, int items_count)
{
    if( items_count == 0) return NULL;

    sNode node;
    node = (sNode)malloc(sizeof(struct node));
    if( node == NULL ) return node;

    int left_tree_count  = items_count / 2;
    int right_tree_count = items_count - left_tree_count - 1;

    node->item = items;
    node->node_left  = tre_create_nodes(items + 1, left_tree_count);
    node->node_right = tre_create_nodes(items + 1 + left_tree_count, right_tree_count);
    return node;
}

int tre_scan (handle_node hdl_node)
{  /*-----------------------------------------------
   || 0: помилка;                                 ||
   || 1: знайшли;                                 ||
   ||-1: 1)успішно оброблено;                     ||
   ||      перехід до наступного вузла дозволено; ||
   ||    2)не знайдено (не виконано)              ||
   -----------------------------------------------*/
    sTree tree = _TREE_CURRENT;
    if( tree->tree_root == NULL) return -1;
    int item_counter = 0;
    return tre_scan_nodes(&tree->tree_root, 0, &item_counter, hdl_node);
}

int tre_scan_nodes(sNode * node, int node_level, int * item_number, handle_node hdl_node)
{  /*-----------------------------------------------
   || 0: помилка;                                 ||
   || 1: знайшли;                                 ||
   ||-1: 1)успішно оброблено;                     ||
   ||      перехід до наступного вузла дозволено; ||
   ||    2)не знайдено (не виконано)              ||
   -----------------------------------------------*/
    if( (*node) == NULL) return -1;

    sTree tree          = _TREE_CURRENT;
    sNode node_left     = (*node)->node_left;
    sNode node_right    = (*node)->node_right;
    int   handle_result = 0;
    int   scan_type     = tree->scan_type;
                          /* 0: _Root_LeftRight ||
                          || 1: Left_Root_Right ||
                          || 2: LeftRight_Root_ */

    if( scan_type == 0 &&
       (handle_result = hdl_node(node, node_level, ++*item_number)) >= 0 )
            return handle_result;

    if( (handle_result = tre_scan_nodes(&node_left, node_level + 1, item_number, hdl_node)) >= 0 )
        return handle_result;

    if( scan_type == 1 &&
       (handle_result = hdl_node(node, node_level, ++*item_number)) >= 0 )
            return handle_result;

    if( (handle_result = tre_scan_nodes(&node_right, node_level + 1, item_number, hdl_node)) >= 0 )
        return handle_result;

    if( scan_type == 2 )
       handle_result = hdl_node(node, node_level, ++*item_number);

    return handle_result;
}

void tre_delete()
{
    sTree * ptr_tree = &_TREE_CURRENT;
    (*ptr_tree)->scan_type = RT_L_R;
    (*ptr_tree)->scan(tre_erase_node);

    free(*ptr_tree);
    *ptr_tree = NULL;
}

int tre_erase_node(sNode * node_to_erase)
{
    int * test_int = (int *)(&node_to_erase + 1);
    printf("%2d: DEL LEVEL %d: %s\n",
            *(test_int + 1),
            *test_int,
            (*node_to_erase)->item->club_name
          );

    free((*node_to_erase)->item);
    free(*node_to_erase);
    *node_to_erase = NULL;
    return -1;
}
