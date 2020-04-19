#ifndef QUEUE_H
#define QUEUE_H

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

typedef struct queue
{
    sNode queue_head;
    sNode queue_tail;
    int   queue_count;
} * sQueue;

bool      que_init        (sQueue *);
bool      que_is_empty    (sQueue);
sNode     que_get_head    (sQueue);
sNode     que_get_tail    (sQueue);
bool      que_is_head     (sQueue, const sNode);
bool      que_is_tail     (sQueue, const sNode);
void      que_delete      (sQueue *);

sNode     que_create_node (sItem);
sNode     que_push        (sQueue, const sNode);
sItem     que_pop         (sQueue);

#endif // QUEUE_H
