#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "clubs.h"

typedef sClub sItem;

typedef struct node
{
    sItem         item;
    struct node * node_next;
    struct node * node_prev;
} * sNode;

typedef struct stack
{
    sNode stack_head;
    sNode stack_tail;
    int   stack_count;
} * sStack;

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

#endif // STACK_H
