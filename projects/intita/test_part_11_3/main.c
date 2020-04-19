/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 11. Динамічні структури даних (частина 1).
 * Частина 3. Додавання елемента на вершину стека.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 25.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Перепишіть процедуру Push() , використовуючи винятково синтаксис С
(вхідний параметр типу Stack передавайте як покажчик на покажчик,
в потрібних місцях тіла процедури відпоівідні поля структури стека
- розіменовуйте).
*/

#include "stack.h"

/*------------------------------------------------------
typedef struct club * sClub;
sClub cls_new_club(char *, ...);
--------------------------------------------------------
typedef sClub          sItem;
typedef struct node  * sNode;
typedef struct stack * sStack;

bool      stk_init        (sStack *);
bool      stk_is_empty    (sStack);
sNode     stk_get_head    (sStack);
sNode     stk_get_tail    (sStack);
bool      stk_is_head     (sStack, const sNode);
bool      stk_is_tail     (sStack, const sNode);
void      stk_delete      (sStack *);

sNode     stk_create_node (sItem);
sNode     stk_push        (sStack, const sNode);
void      stk_delete_node (sStack,       sNode *);

void      printStack      (sStack);
void      printNode       (const sNode,  int);
------------------------------------------------------*/

int main(void)
{
    sItem  item      = NULL;
    sStack stack     = NULL;
    sNode  node      = NULL;

    puts("\0");
//---------------------------- stk_init ----------------------------------------
    stk_init(&stack);
//------------------------- stk_create_node stk_push ---------------------------
    item = cls_new_club("Super Club 2", "Club City 2", "Club Country 2", 200.5, 228);
    node = stk_create_node(item);   
    stk_push(stack, node);
    puts("stk_push:        Club 2");
    printStack(stack);
//------------------------- stk_create_node stk_push ---------------------------
    item = cls_new_club("Super Club 1", "Club City 1", "Club Country 1", 100.5, 128);
    node = stk_create_node(item);
    stk_push(stack, node);
    puts("stk_push:        Club 1");
    printStack(stack);
//------------------------- stk_create_node stk_push ---------------------------
    item = cls_new_club("Super Club 3", "Club City 3", "Club Country 3", 300.5, 328);
    node = stk_create_node(item);
    stk_push(stack, node);
    puts("stk_push:        Club 3");
    printStack(stack);
//------------------------- stk_create_node stk_push ---------------------------
    item = cls_new_club("Super Club 4", "Club City 4", "Club Country 4", 400.5, 428);
    node = stk_create_node(item);
    stk_push(stack, node);
    puts("stk_push:        Club 4");
    printStack(stack);
//------------------------------ stk_delete_node -------------------------------
    node = stk_get_head(stack);
    while( node != NULL )
    {
        puts("stk_delete_node: HEAD");
        stk_delete_node(stack, &node);
        printStack(stack);
        node = stk_get_head(stack);
    }
//--------------------------------- stk_delete ---------------------------------
    stk_delete(&stack);
//------------------------------------------------------------------------------
    puts("\0");
    return 0;
}
