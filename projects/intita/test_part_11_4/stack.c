#include "clubs.h"
#include "stack.h"

static void stk_erase_node(sNode *);

bool stk_init(sStack * ptr_stack)
{
    sStack stack = NULL;

    stack = (sStack)malloc(sizeof(struct stack));

    if( stack == NULL ) return false;

    stack->stack_head = NULL;
    stack->stack_tail = NULL;
    stack->stack_count = 0;

    *ptr_stack = stack;

    return true;
}

bool stk_is_empty(sStack stack)
{ return stack->stack_head == NULL; }

sNode stk_get_head(sStack stack)
{ return stack->stack_head; }

sNode stk_get_tail(sStack stack)
{ return stack->stack_tail; }

bool stk_is_head(sStack stack, const sNode node)
{ return stack->stack_head == node; }

bool stk_is_tail(sStack stack, const sNode node)
{ return stack->stack_tail == node; }

sNode stk_create_node(sItem item)
{
    sNode node;
    node = (sNode)malloc(sizeof(struct node));

    if( node == NULL) return node;

    node->item = item;
    node->node_next = NULL;
    node->node_prev = NULL;
    return node;
}

sNode stk_push(sStack stack, const sNode node_to_push)
{
    if( stk_is_empty(stack) )
    {
        stack->stack_head = node_to_push;
        stack->stack_tail = node_to_push;
        stack->stack_count = 1;
        return node_to_push;
    }

    sNode node_head = stk_get_head(stack);

    node_to_push->node_next = node_head;
    node_head->node_prev = node_to_push;
    stack->stack_head = node_to_push;
    stack->stack_count++;

    return node_to_push;
}

sItem stk_pop(sStack stack)
{
    if( stk_is_empty(stack) ) return NULL;

    sNode node = stk_get_head(stack);
    sItem item = node->item;
    node->item = NULL;
    stk_delete_node(stack, &node);

    return item;
}

void stk_delete_node(sStack stack, sNode * ptr_node_to_delete)
{
    sNode node_to_delete  = *ptr_node_to_delete;

    if( stk_is_head(stack, node_to_delete) )
    {
        stack->stack_head = node_to_delete->node_next;

        if( stk_is_tail(stack, node_to_delete) )
            stack->stack_tail = NULL;
        else
            node_to_delete->node_next->node_prev = NULL;
    }
    else
    {
        node_to_delete->node_prev->node_next = node_to_delete->node_next;
        if( stk_is_tail(stack, node_to_delete) )
            stack->stack_tail = node_to_delete->node_prev;
        else
            node_to_delete->node_next->node_prev = node_to_delete->node_prev;
    }

    stack->stack_count--;
    stk_erase_node(ptr_node_to_delete);
}

void stk_erase_node(sNode * node_to_erase)
{
    free((*node_to_erase)->item);
    free(*node_to_erase);
    *node_to_erase = NULL;
}

void stk_delete(sStack * ptr_stack)
{
    sNode node_current   = stk_get_head(*ptr_stack);
    sNode node_to_delete = NULL;

    while( node_current )
    {
        node_to_delete = node_current;
        node_current = node_to_delete->node_next;
        stk_erase_node(&node_to_delete);
    }

    free(*ptr_stack);
    *ptr_stack = NULL;
}

void printStack(const sStack stack)
{
    if( stack == NULL ) return;

    int i = 0;
    sNode node = stk_get_head(stack);

    puts("\0");
    puts("  ----------------------------------------------------------------------------------------------------");
    puts("  | N| place |     club     |     city     |     country     | revenue |   club next  |   club prev  |");
    puts("  ----------------------------------------------------------------------------------------------------");

    for(i = 0; i < stack->stack_count; i++)
    {
        printNode(node, i + 1);
        node = node->node_next;
    }
    puts("  ----------------------------------------------------------------------------------------------------");
    printf("  |                                                                    ");
    printf("|     count    |    %4d      |\n", stack->stack_count);
    puts("  ----------------------------------------------------------------------------------------------------");
    puts("\0");
}

void printNode(const sNode node, int list_number)
{
    if( node == NULL ) return;

    printf("  |%2d|%5d  |%-14s|%-14s|%-17s| %7.2f |",
                                       list_number,
                                       node->item->club_place,
                                       node->item->club_name,
                                       node->item->club_city,
                                       node->item->club_country,
                                       node->item->club_revenue);
    if( node->node_next == NULL )
        printf("   (null)     |");
    else
        printf("%-14s|", node->node_next->item->club_name);

    if( node->node_prev == NULL )
        printf("   (null)     |");
    else
        printf("%-14s|", node->node_prev->item->club_name);

    puts("\0");
}
