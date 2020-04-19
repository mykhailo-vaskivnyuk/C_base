#include "clubs.h"
#include "tree.h"
//----------------------------------------------------------
static sTree _TREE_CURRENT;
/*----------------------------------------------------------
bool  tre_init        (sTree *);
bool  tre_set_current (sTree);
sNode tre_create_node (sItem);
----------------------------------------------------------*/
typedef int (*handle_node)();
//--- methods ----------------------------------------------
static bool  tre_create      (sItem,   int, int);
static int   tre_scan        (handle_node);
static int   tre_scan_nodes  (sNode *, int, int *, handle_node);
static sNode tre_add_node    (sNode);
static void  tre_delete      ();
//--- handles ----------------------------------------------
static int  tre_add_node_hdl(sNode *);
//----------------------------------------------------------
static sNode tre_create_nodes(sItem, int);
static int   tre_erase_node  (sNode *);
//----------------------------------------------------------

bool tre_init(sTree * ptr_tree)
{
    sTree tree = (sTree)malloc(sizeof(struct tree));
    if( tree == NULL ) return false;

    _TREE_CURRENT    = tree;
    tree->tree_root  = NULL;
    tree->tree_count = 0;

    tree->scan_type  = 0; // 0: _Root_LeftRight ||
                          // 1: Left_Root_Right ||
                          // 2: LeftRight_Root_ ||
    tree->create      = tre_create;
    tree->scan        = tre_scan;
    tree->scan_nodes  = tre_scan_nodes;
    tree->add_node    = tre_add_node;
    tree->delete_tree = tre_delete;
    *ptr_tree = tree;
    return true;
}

bool tre_set_current (sTree tree)
{
    _TREE_CURRENT = tree;
    return true;
}

sNode tre_create_node(sItem item)
{
    sNode node;
    node = (sNode)malloc(sizeof(struct node));

    if( node == NULL) return node;

    node->item       = item;
    node->node_count = 1;
    node->node_left  = NULL;
    node->node_right = NULL;
    return node;
}

void tre_delete()
{
    sTree * ptr_tree = &_TREE_CURRENT;
    (*ptr_tree)->scan_type = RT_L_R;
    tre_scan(tre_erase_node);

    free(*ptr_tree);
    *ptr_tree = NULL;
}

bool tre_create(sItem items, int items_count, int type_of_create)
{
    sTree tree = _TREE_CURRENT;
    int   i    = 0;
    if( type_of_create == 0 )
        tree->tree_root = tre_create_nodes(items, items_count);
    else
    {
        for(i = 0; i < items_count; i++)
            tre_add_node(tre_create_node(items + i));
    }
    return true;
}

sNode tre_create_nodes(sItem items, int items_count)
{
    if( items_count == 0) return NULL;
    sTree tree = _TREE_CURRENT;
    sNode node = tre_create_node(items);

    if( node == NULL ) return NULL;
    else tree->tree_count++;

    int left_tree_count  = items_count / 2;
    int right_tree_count = items_count - left_tree_count - 1;

    node->node_left  = tre_create_nodes(items + 1, left_tree_count);
    node->node_right = tre_create_nodes(items + 1 + left_tree_count, right_tree_count);

    return node;
}

int tre_scan (handle_node hdl_node)
{  /*-- return -------------------------------------
   || 0: помилка;                                 ||
   || 1: знайшли;                                 ||
   ||-1: 1)успішно оброблено;                     ||
   ||      перехід до наступного вузла дозволено; ||
   ||    2)не знайдено (не виконано)              ||
   -----------------------------------------------*/
    sTree tree = _TREE_CURRENT;
    if( tree->tree_root == NULL)
    {
        tree->active_node_ptr = &tree->tree_root;
        return -1;
    }
    int scan_result = 0;
    int item_counter = 0;

    scan_result = tre_scan_nodes(&tree->tree_root, 0, &item_counter, hdl_node);

    return scan_result;
}

int tre_scan_nodes(sNode * node, int node_level, int * item_number, handle_node hdl_node)
{  /*-- return -------------------------------------
   || 0: помилка;                                 ||
   || 1: знайшли (вільне місце)                   ||
   || 2: знайшли однаковий;                       ||
   ||-1: 1)успішно оброблено;                     ||
   ||      перехід до наступного вузла дозволено; ||
   ||    2)не знайдено (не виконано)              ||
   ||-2: скануємо лише ліву гілку                 ||
   ||-3: скануємо лише праву гілку                ||
   -----------------------------------------------*/

    if( (*node) == NULL ) return -1;

    sTree tree          = _TREE_CURRENT;
    sNode node_left     = (*node)->node_left;
    sNode node_right    = (*node)->node_right;
    int   handle_result = -1;
    int   scan_type     = tree->scan_type;
                          /* 0: _Root_LeftRight ||
                          || 1: Left_Root_Right ||
                          || 2: LeftRight_Root_ */
    if( scan_type == 0 &&
       (handle_result = hdl_node(node, node_level, ++*item_number)) >= 0 )
        return handle_result;

    if( (handle_result == -1 || handle_result == -2) &&
        (handle_result = tre_scan_nodes(&node_left, node_level + 1, item_number, hdl_node)) >= 0 )
        return handle_result;

    if( scan_type == 1 &&
       (handle_result = hdl_node(node, node_level, ++*item_number)) >= 0 )
            return handle_result;

    if( (handle_result == -1 || handle_result == -3) &&
        (handle_result = tre_scan_nodes(&node_right, node_level + 1, item_number, hdl_node)) >= 0 )
        return handle_result;

    if( scan_type == 2 )
       handle_result = hdl_node(node, node_level, ++*item_number);

    return handle_result;
}

//------------------------------------------------------------------------------
//  METHODS
//-----------------------------------------------------------------------------=
sNode tre_add_node (sNode node)
{
    sTree tree = _TREE_CURRENT;
    tree->scan_type = RT_L_R;
    tree->active_node_ptr = &node;

    if( tree->tree_root == NULL )
    {
        tree->tree_root = node;
        //tree->active_node_ptr = &node;
        //tree->tree_count++;
        //return node;
    }
    else
    {
        //tree->scan_type = RT_L_R;
        //tree->active_node_ptr = &node;
        if( tre_scan(tre_add_node_hdl) == 2)
        {
            //puts("hello"); exit(0);
            //printf("%s\n", (*tree->active_node_ptr)->item->club_name); exit(0);
            (*tree->active_node_ptr)->node_count += 1;
            return *tree->active_node_ptr;
        }
        else
            *tree->active_node_ptr = node;
    }

    tree->tree_count++;
    return node;
}

//------------------------------------------------------------------------------
//  HANDLES
//-----------------------------------------------------------------------------=

static int tre_add_node_hdl(sNode * node_to_find) // * ???
{ /*-- return -------------------------------------
  || 1: знайшли, вузол для приєднання            ||
  ||    нового вузла                             ||
  || 2: знайшли однаковий елемент                ||
  -----------------------------------------------*/
    sTree tree = _TREE_CURRENT;
    int handle_result;
    handle_result = tree->cmp_nodes(*tree->active_node_ptr, *node_to_find);

    if( handle_result == 0 )
    {
        tree->active_node_ptr = node_to_find;
        return 2;
    }

    handle_result = ( handle_result < 0) ? -2 : -3;

    if( (handle_result == -2 && (*node_to_find)->node_left == NULL) )
    {
        tree->active_node_ptr = &((*node_to_find)->node_left);
        return 1;
    }

    if( (handle_result == -3 && (*node_to_find)->node_right == NULL) )
    {
        tree->active_node_ptr = &((*node_to_find)->node_right);
        return 1;
    }

    return handle_result;
}

//------------------------------------------------------------------------------
//  OTHERS
//-----------------------------------------------------------------------------=

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
