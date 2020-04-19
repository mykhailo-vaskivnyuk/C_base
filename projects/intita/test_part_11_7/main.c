/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 11. Динамічні структури даних (частина 2).
 * Частина 6. Додавання елемента в кінець черги.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 25.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Сформуйте структуру Club, яка містить дані про такі турнірні результати футбольного клубу:
- назва футбольного клубу (символьний рядок);
- місто, яке представляє клуб (символьний рядок);
- кількість забитих м'ячів;
- кількість пропущених м'ячів;
- кількість набраних очок.
*/

#include "queue.h"

/*------------------------------------------------------
typedef struct club * sClub;
sClub cls_new_club(char *, ...);
--------------------------------------------------------
typedef sClub          sItem;
typedef struct node  * sNode;
typedef struct queue * sQueue;

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
------------------------------------------------------*/

void      printQueue      (sQueue);
void      printNode       (const sNode,  int);

int main(void)
{
    sItem  item      = NULL;
    sQueue queue     = NULL;
    sNode  node      = NULL;

    puts("\0");
//-------------------------------- que_init ------------------------------------
    que_init(&queue);
//------------------------- que_create_node que_push ---------------------------
    item = cls_new_club("Super Club 2", "Club City 2", "Club Country 2", 200.5, 228);
    node = que_create_node(item);
    que_push(queue, node);
    puts("que_push:        Club 2");
    printQueue(queue);
//------------------------- que_create_node que_push ---------------------------
    item = cls_new_club("Super Club 1", "Club City 1", "Club Country 1", 100.5, 128);
    node = que_create_node(item);
    que_push(queue, node);
    puts("que_push:        Club 1");
    printQueue(queue);
//------------------------- que_create_node que_push ---------------------------
    item = cls_new_club("Super Club 3", "Club City 3", "Club Country 3", 300.5, 328);
    node = que_create_node(item);
    que_push(queue, node);
    puts("que_push:        Club 3");
    printQueue(queue);
//------------------------- que_create_node que_push ---------------------------
    item = cls_new_club("Super Club 4", "Club City 4", "Club Country 4", 400.5, 428);
    node = que_create_node(item);
    que_push(queue, node);
    puts("que_push:        Club 4");
    printQueue(queue);
//--------------------------------- que_pop ------------------------------------
    while( (item = que_pop(queue)) )
    {
        printf("que_pop:     %s\n", item->club_name);
        free(item);
        printQueue(queue);
    }
//--------------------------------- que_delete ---------------------------------
    que_delete(&queue);
//------------------------------------------------------------------------------
    puts("\0");
    return 0;
}

void printQueue(const sQueue queue)
{
    if( queue == NULL ) return;

    int i = 0;
    sNode node = que_get_head(queue);

    puts("\0");
    puts("  ----------------------------------------------------------------------------------------------------");
    puts("  | N| place |     club     |     city     |     country     | revenue |   club next  |   club prev  |");
    puts("  ----------------------------------------------------------------------------------------------------");

    for(i = 0; i < queue->queue_count; i++)
    {
        printNode(node, i + 1);
        node = node->node_next;
    }
    puts("  ----------------------------------------------------------------------------------------------------");
    printf("  |                                                                    ");
    printf("|     count    |    %4d      |\n", queue->queue_count);
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
