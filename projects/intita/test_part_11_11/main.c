/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 11. Динамічні структури даних (частина 2).
 * Частина 11. Алгоритми роботи з деревами. Побудова дерева з мінімальною висотою.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 29.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Сформуйте масив структур типу Club з полями, описаними в частині
   6 даного заняття (введення даних в масив - з клавіатури або файлу).
2. Запрограмуйте мінімальне за висотою дерево (використовуючи синтаксис С),
   у вершинах якого містилися б дані про клуби з утвореного масиву.
   Ключове поле кожної вершини - кількість набраних очок.
*/

#include "tree.h"

/*--- clubs.h ----------------------------------------------
typedef struct club * sClub;

sClub cls_new_club    (char *, ...);

int   readClubs       (sClub *, char *, int,    in_func_ptr);
int   inputNumber     (void);
int   inputClubsTxt   (sClub *, int *,  FILE *, int);
void  printClubs      (sClub,   int);
void  printClub       (sClub,   int);
void  freeClubs       (sClub *, int*);
----- tree.h -----------------------------------------------
typedef sClub           sItem;
typedef struct node   * sNode;
typedef struct tree   * sTree;
typedef enum SCAN_TYPES eSCAN_TYPES

bool  tre_init        (sTree *);
bool  tre_set_current (sTree);
void  tre_delete      ();
----- tree methods -----------------------------------------
typedef int (*handle_node)(sNode * node[, int node_level]);

bool  tree.tre_create     (sItem, int);
int   tree.tre_scan       (handle_node);
int   tree.tre_scan_nodes (sNode *, int, handle_node);
----------------------------------------------------------*/

void  printTree(sTree,   eSCAN_TYPES);
int   printNode(sNode *, int);

int main(void)
{
    sItem  items       = NULL;
    int    items_count = 0;
    char * file_name   = "teams.txt";
    sTree  tree        = NULL;

    puts("\0");
//------------------------------- readClubs ------------------------------------
    items_count = readClubs(&items, file_name,  inputNumber(), inputClubsTxt);
    printClubs(items, items_count);
//------------------------------- tre_init -------------------------------------
    tre_init(&tree);
//------------------------------- tre_create -----------------------------------
    tree->create(items, items_count);
    freeClubs(&items, &items_count);
//------------------------------- print tree КЛП -------------------------------
    printf("PRINT ROOT-LEFT-RIGHT\n");
    puts("\0");
    printTree(tree, RT_L_R);
//------------------------------- print tree ЛКП -------------------------------
    printf("PRINT LEFT-ROOT-RIGHT\n");
    puts("\0");
    printTree(tree, L_RT_R);
//------------------------------- print tree ЛПК -------------------------------
    printf("PRINT LEFT-RIGHT-ROOT\n");
    puts("\0");
    printTree(tree, L_R_RT);
//------------------------------- tre_delete -----------------------------------
    printf("PRINT TREE AFTER DELETE\n");
    puts("\0");
    tre_delete();
    printTree(tree, RT_L_R);
//------------------------------------------------------------------------------
    puts("\0");
    return 0;
}

void printTree(sTree tree, eSCAN_TYPES scan_type)
{
    tre_set_current(tree);
    tree->scan_type = scan_type;
    tree->scan(printNode);
}

int printNode(sNode * node, int node_level)
{/*-------------------------------------------------
   || 0: помилка;                                 ||
   || 1: знайшли;                                 ||
   ||-1: 1)успішно оброблено;                     ||
   ||      перехід до наступного вузла дозволено; ||
   ||    2)не знайдено (не виконано)              ||
   -------------------------------------------------*/
    int tab_and_space_size = 40;
    int tab_size           = 8 * node_level;
    int space_size         = tab_and_space_size - tab_size;

    char tab[tab_size + 1];
    char space[space_size + 1];

    memset(tab, '-', tab_size);
    tab[tab_size] = '\0';

    memset(space, '.', space_size);
    space[space_size] = '\0';

    printf("%slevel%2d %s %s\n\n", tab, node_level, space, (*node)->item->club_name);

    return -1;
}
