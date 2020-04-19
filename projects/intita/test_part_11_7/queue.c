#include "clubs.h"
#include "queue.h"

static void que_erase_node  (sNode *);
static void que_delete_node (sQueue, sNode *);

bool que_init(sQueue * ptr_queue)
{
    sQueue queue = NULL;

    queue = (sQueue)malloc(sizeof(struct queue));

    if( queue == NULL ) return false;

    queue->queue_head = NULL;
    queue->queue_tail = NULL;
    queue->queue_count = 0;

    *ptr_queue = queue;

    return true;
}

bool que_is_empty(sQueue queue)
{ return queue->queue_head == NULL; }

sNode que_get_head(sQueue queue)
{ return queue->queue_head; }

sNode que_get_tail(sQueue queue)
{ return queue->queue_tail; }

bool que_is_head(sQueue queue, const sNode node)
{ return queue->queue_head == node; }

bool que_is_tail(sQueue queue, const sNode node)
{ return queue->queue_tail == node; }

sNode que_create_node(sItem item)
{
    sNode node;
    node = (sNode)malloc(sizeof(struct node));

    if( node == NULL) return node;

    node->item = item;
    node->node_next = NULL;
    node->node_prev = NULL;
    return node;
}

sNode que_push(sQueue queue, const sNode node_to_push)
{
    if( que_is_empty(queue) )
        queue->queue_head = node_to_push;
    else
    {
        sNode node_tail = que_get_tail(queue);

        node_to_push->node_prev = node_tail;
        node_tail->node_next = node_to_push;
    }
    queue->queue_tail = node_to_push;
    queue->queue_count++;
    return node_to_push;
}

sItem que_pop(sQueue queue)
{
    if( que_is_empty(queue) ) return NULL;

    sNode node = que_get_head(queue);
    sItem item = node->item;
    node->item = NULL;
    que_delete_node(queue, &node);

    return item;
}

void que_delete_node(sQueue queue, sNode * ptr_node_to_delete)
{
    sNode node_to_delete  = *ptr_node_to_delete;

    if( que_is_head(queue, node_to_delete) )
    {
        queue->queue_head = node_to_delete->node_next;

        if( que_is_tail(queue, node_to_delete) )
            queue->queue_tail = NULL;
        else
            node_to_delete->node_next->node_prev = NULL;
    }
    else
    {
        node_to_delete->node_prev->node_next = node_to_delete->node_next;
        if( que_is_tail(queue, node_to_delete) )
            queue->queue_tail = node_to_delete->node_prev;
        else
            node_to_delete->node_next->node_prev = node_to_delete->node_prev;
    }

    queue->queue_count--;
    que_erase_node(ptr_node_to_delete);
}

void que_erase_node(sNode * node_to_erase)
{
    free((*node_to_erase)->item);
    free(*node_to_erase);
    *node_to_erase = NULL;
}

void que_delete(sQueue * ptr_queue)
{
    sNode node_current   = que_get_head(*ptr_queue);
    sNode node_to_delete = NULL;

    while( node_current )
    {
        node_to_delete = node_current;
        node_current = node_to_delete->node_next;
        que_erase_node(&node_to_delete);
    }

    free(*ptr_queue);
    *ptr_queue = NULL;
}
