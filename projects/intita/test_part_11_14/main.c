/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 11. Динамічні структури даних (частина 2).
 * Частина 14. Реалізація пошуку в дереві.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 05.07.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Перепишіть процедуру AddToTree() (частина 13),
   використовуючи в якості ключа кількість набраних клубом очок.
2. На основі попереднього аналізу алгоритмів обходу дерева (ЛКП, КЛП і ЛПК),
   з'ясуйте, який з них забезпечує виведення під час обходу
   значення ключів (цілих чисел) за спаданням.
3. Застосуйте вибраний алгоритм обходу до щойно сформованого дерева.
   Переконайтесь, що послідовність виведених на екран клубів
   відповідає порядку традиційної турнірної таблиці змагань
   (від найбільшої до найменшої кількості очок).
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
sNode tre_create_node (sItem);
----- tree methods -----------------------------------------
typedef int (*handle_node)([sNode * node[, int node_level[, int * item_number]]]);

bool  tree.create      (sItem,   int, int);
int   tree.scan        (handle_node);
int   tree.scan_nodes  (sNode *, int, int *, handle_node);
sNode tree.add_node    (sNode);
void  tree.delete_tree ();
----------------------------------------------------------*/
void  printTree   (sTree,   eSCAN_TYPES);
int   printNode   (sNode *, int, int);
int   cmpClubName (sNode,   sNode);
int   cmpClubPlace(sNode,   sNode);

int main(void)
{
    sItem  items       = NULL;
    int    items_count = 0;
    char * file_name   = "teams.txt";
    sTree  tree        = NULL;
//------------------------------------------------------------------------------
    puts("\0");
//------------------------------- readClubs ------------------------------------
    items_count = readClubs(&items, file_name,  inputNumber(), inputClubsTxt);
    printClubs(items, items_count);
//------------------------------- tre_init -------------------------------------
    tre_init(&tree);
    tree->cmp_nodes = cmpClubPlace; //cmpClubName;
//------------------------------- tre_create -----------------------------------
    tree->create(items, items_count, 1); /* 0: min || 1: key */
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
    tree->delete_tree();
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

    if( tab_size > tab_and_space_size ) tab_size = tab_and_space_size;
    if( space_size < 0 ) space_size = 0;

    char tab[tab_size + 1];
    char space[space_size + 1];

    memset(tab, '-', tab_size);
    tab[tab_size] = '\0';

    memset(space, '.', space_size);
    space[space_size] = '\0';

    printf("%slevel%2d %s ", space, node_level, tab);

    printClub((*node)->item, item_number);

    memset(tab, ' ', strlen(tab));
    memset(space, ' ', strlen(space));

    printf("%s        %s ", tab, space);
    printClub(NULL, 0);

    return -1;
}

int cmpClubName(sNode node_current, sNode node_to_compare)
{
    return strcmp(node_to_compare->item->club_name,
                  node_current->item->club_name);
}

int cmpClubPlace(sNode node_current, sNode node_to_compare)
{
    return  node_to_compare->item->club_place
           -node_current->item->club_place;
}
