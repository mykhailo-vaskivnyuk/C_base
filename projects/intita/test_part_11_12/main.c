/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 11. Динамічні структури даних (частина 2).
 * Частина 12. Обхід дерева.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 30.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Реалізуйте процедуру PrintLKP() для обходу раніше створеного
   дерева з даними про футбольні клуби. На екран виводьте дані
   всіх полів (назва, місто, забиті-пропущені м'ячі, очки).
2. За аналогією з варіантом ЛКП – запрограмуйте процедури,
   що реалізують варіанти КЛП і ЛПК. Застосуйте їх до вказаного дерева
   з клубами, порівняйте результати обходу дерева (порядок виведення даних про клуби на екран).
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
typedef int (*handle_node)([sNode * node[, int node_level[, int * item_number]]]);

bool  tree.tre_create     (sItem,   int);
int   tree.tre_scan       (handle_node);
int   tree.tre_scan_nodes (sNode *, int, int *, handle_node);
----------------------------------------------------------*/

void  printTree(sTree,   eSCAN_TYPES);
int   printNode(sNode *, int, int);

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
    printTree(tree, RT_L_R);
//------------------------------- print tree ЛКП -------------------------------
    printf("PRINT LEFT-ROOT-RIGHT\n");
    printTree(tree, L_RT_R);
//------------------------------- print tree ЛПК -------------------------------
    printf("PRINT LEFT-RIGHT-ROOT\n");
    printTree(tree, L_R_RT);
//------------------------------- tre_delete -----------------------------------
    tre_delete();
    puts("\0");
    printf("PRINT TREE AFTER DELETE\n");
    printTree(tree, RT_L_R);
//------------------------------------------------------------------------------
    puts("\0");
    return 0;
}

void printTree(sTree tree, eSCAN_TYPES scan_type)
{
    char space[44];
    memset(space, ' ', sizeof(space));

    printf(space);
    puts("----------------------------------------------");
    printf(space);
    puts("| N| place | score |    club    |    city    |");
    printf(space);
    puts("----------------------------------------------");

    tre_set_current(tree);
    tree->scan_type = scan_type;
    tree->scan(printNode);

    printf(space);
    puts("----------------------------------------------");
    puts("\0");
}

int printNode(sNode * node, int node_level, int item_number)
{/*-------------------------------------------------
   || 0: помилка;                                 ||
   || 1: знайшли;                                 ||
   ||-1: 1)успішно оброблено;                     ||
   ||      перехід до наступного вузла дозволено; ||
   ||    2)не знайдено (не виконано)              ||
   -------------------------------------------------*/
    int tab_and_space_size = 35;
    int tab_size           = 8 * node_level;
    int space_size         = tab_and_space_size - tab_size;

    char tab[tab_size + 1];
    char space[space_size + 1];

    memset(tab, '-', tab_size);
    tab[tab_size] = '\0';

    memset(space, '.', space_size);
    space[space_size] = '\0';

    //printf("%slevel%2d %s ", tab, node_level, space);
    printf("%slevel%2d %s ", space, node_level, tab);
    printClub((*node)->item, item_number);

    memset(tab, ' ', strlen(tab));
    memset(space, ' ', strlen(space));

    printf("%s        %s ", tab, space);
    printClub(NULL, 0);

    return -1;
}
