/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Проміжний тест по темах "Текствові рядки" і "Текстові файли"
 * (комплексне завдання)
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 21.07.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/*
Постановка задачі.
Дано:
 - текстові файли sur.txt i names.txt, що містять переліки:
    sur.txt - 20 прізвищ осіб (укр. мовою) чоловічого роду -
              потенційних претендентів на вакантні посади в щойно створеній компанії;
    names.txt -  20 різних імен (перші 10 - жіночі, наступні 10 - чоловічі);
 - двовимірний масив символів sur[20][30];
 - двовимірний масив символів names[20][20];
 - матриця цілих чисел data[20][4].

Програма повинна виконати наступну обробку початкових даних за допомогою відповідних процедур/функцій:
 - процедура readFiles() - iніціалізує масиви sur i names шляхом читання даних з відповідних файлів;
 - процедура fixSex()    - здійснює фіксацію випадковим чином (або шляхом введення з клавіатури)
   статі кожної особи (0 - чол, 1 - жін); результати (послідовність нулів і одиниць)
   зберегти в 1-му стовпчику матриці data;
 - процедура changeSur() - виконює зміну закінчень деяких прізвищ (що закінчуються на "ов", "ін" та "ий"),
   якщо буде виявлено, що вони належать особам жіночої статі (відповідно - на "ова", "іна" та "а");
 - процедура fixName() - здійснює фіксацію випадковим чином (або шляхом введення з клавіатури)
   імені кожної особи шляхом вказання його порядкового номера з масиву names (0-9: жіночі; 10-19: чоловічі);
   вибір жіночого або чоловічого імені має відбуватись в залежності від результатів,
   встановлених процедурою fixSex(); результат - в 2-й стовпчик матриці data;
 - процедура fixAge() - генерує випадковим чином (або шляхом введення з клави) послідовності чисел
   в діапазоні 18-60 (вік особи), результат - в 3-й стовпчик матриці data;
 - функція fixRange() - повертає мінімальне/максимальне значення віку, встановленого компанією
   для претендентів (генерує випадково або пропонує ввести з клави).
   Діапазон для мінімального віку: 18-25, для максимального: 45-60.
 - функція filterAppl() - повертає 1 або 0 в залежності від того, підходить чи не підходить компанії
   кожен з предендентів за своїм віком (орієнтуючись на встановлений функцією fixRange() діапазон).
   Результат - в 4-й стовпчик матриці data;
 - функція midAge() - повертає середній вік (значення типу float) для жінок/чоловіків,
   які були прийняті на роботу в компанію (за результатами функції filterAppl() ).
 - процедура outData() - аналізує всі опрацьовані дані і виводить у текстовий файл res.txt дані
   по кожній з 20-ти осіб в такій послідовності: прізвище - ім'я - стать - вік - співробітник.
   Примітка: в колонці "стать" писати "чол/жін", в колонці "співробітник" - "так/ні"
   (залежно від того, прийнятий чи не прийнятий на роботу).
   Нижче окремими рядками вивести середній вік жінок і чоловіків, які були прийняті на роботу.
*/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

#define SURNAME_MAX_LEN 15 //кількість літер в прізвищі
#define NAME_MAX_LEN    10 //кількість літер в імені
#define EMPLS_COUNT     20
#define SURNAMES_FILE   "sur.txt"
#define NAMES_FILE      "names.txt"
#define RESULT_FILE     "res.txt"
#define AGE_START_1     18
#define AGE_START_2     25
#define AGE_END_1       45
#define AGE_END_2       60
#define SRAND           2000
#define CODE_PAGE       "65001" //utf-8

typedef enum data_fields
{
    SEX
   ,NAME_INDEX
   ,AGE
   ,EMPL
   ,DFS_END
} eDataFields;

typedef enum sex
{
    MAN
   ,WOMAN
} eSEX;

typedef struct employees
{
    char * surnames_file_name;
    char * names_file_name;
    char * result_file_name;
    int    empls_count;
    int    surname_max_len;
    int    name_max_len;
    int    age_start_1;
    int    age_start_2;
    int    age_end_1;
    int    age_end_2;
    FILE * empls_fl;

    char * surnames;
    char * names;
    int  * data;
    int    age_min;
    int    age_max;
    float  age_mid_mn;
    float  age_mid_wn;

    void (*readFiles)();
    void (*fixSex)();
    void (*changeSur)();
    void (*fixName)();
    void (*fixAge)();
    void (*fixRange)();
    void (*filterAppl)();
    void (*midAge)();
    void (*outData)();

    void (*free)();

} * sEmployees;

static sEmployees EMPLOYEES;

//---- FUNCTIONS BEGIN -------------------------------------------------------//
void readFiles();
void fixSex();
void changeSur();
void fixName();
void fixAge();
void fixRange();
void filterAppl();
void midAge();
void outData();
//----------------------------------------------------------------------------//
void empls_init();
void empls_free();
//----------------------------------------------------------------------------//
void mf_OpenFile (char * file_name, char * file_mode, FILE ** file_ptr_addr);
int  mf_ReadFile (char * file_name, char * array, int array_size_N, int array_size_M);
int  mf_Rnd      (int range_min_value, int range_max_value);
void mf_StrCut   (char * string, char * string_cut);
bool mf_StrRplEnd(char * string, char * string_end, char * string_rpl);
//---- FUNCTIONS END ---------------------------------------------------------//

int main(void)
{
    struct employees empls;

    system("chcp " CODE_PAGE " > null");

    srand(SRAND);

    empls_init(&empls);

    empls.readFiles();
    empls.fixSex();
    empls.changeSur();
    empls.fixName();
    empls.fixAge();
    empls.fixRange();
    empls.filterAppl();
    empls.midAge();
    empls.outData();
    empls.free();

    puts("");
    return 0;
}

void readFiles()
{
    sEmployees empls = EMPLOYEES;

    mf_ReadFile ( empls->surnames_file_name
                , empls->surnames
                , empls->empls_count
                , empls->surname_max_len);

    mf_ReadFile ( empls->names_file_name
                , empls->names
                , empls->empls_count
                , empls->name_max_len);
}

void fixSex()
{
    sEmployees empls = EMPLOYEES;
    int        i     = 0;
    int        index = 0;

    for(i = 0; i < empls->empls_count / 2; i++)
    {
        while( (empls->data)[index = (mf_Rnd(0, empls->empls_count - 1) * DFS_END + SEX)] );
        (empls->data)[index] = WOMAN;
    }
}

void changeSur()
{
    sEmployees empls = EMPLOYEES;
    int i = 0;

    for( i = 0; i < empls->empls_count; i++ )
    {
        if( empls->data[i * DFS_END + SEX] == MAN ) continue;
        if( mf_StrRplEnd((empls->surnames) + i * empls->surname_max_len, "ий", "а") )   continue;
        if( mf_StrRplEnd((empls->surnames) + i * empls->surname_max_len, "ов", "ова") ) continue;
        if( mf_StrRplEnd((empls->surnames) + i * empls->surname_max_len, "єв", "єва") ) continue;
            mf_StrRplEnd((empls->surnames) + i * empls->surname_max_len, "н" , "на");
    }
}

void fixName()
{
    sEmployees empls = EMPLOYEES;
    int i = 0;

    for(i = 0; i < empls->empls_count; i++)
    {
        if( empls->data[i * DFS_END + SEX] == MAN )
            empls->data[i * DFS_END + NAME_INDEX] = mf_Rnd(empls->empls_count / 2, empls->empls_count - 1);
        else
            empls->data[i * DFS_END + NAME_INDEX] = mf_Rnd(0, empls->empls_count / 2 - 1);
    }
}

void fixAge()
{
    sEmployees empls = EMPLOYEES;
    int i = 0;

    for(i = 0; i < empls->empls_count; i++)
        empls->data[i * DFS_END + AGE] = mf_Rnd(empls->age_start_1, empls->age_end_2);
}

void fixRange()
{
    sEmployees empls = EMPLOYEES;

    empls->age_min = mf_Rnd(empls->age_start_1, empls->age_start_2);
    empls->age_max = mf_Rnd(empls->age_end_1, empls->age_end_2);
}

void filterAppl()
{
    sEmployees empls = EMPLOYEES;
    int i = 0;

    for(i = 0; i < empls->empls_count; i++)
    {
        if( empls->data[i * DFS_END + AGE] >= empls->age_min &&
            empls->data[i * DFS_END + AGE] <= empls->age_max)
            empls->data[i * DFS_END + EMPL] = 1;
    }
}

void midAge()
{
    sEmployees empls = EMPLOYEES;
    int i = 0;
    int empls_count_mn = 0;
    int empls_count_wn = 0;

    for(i = 0; i < empls->empls_count; i++)
    {
        if( !empls->data[i * DFS_END + EMPL] ) continue;

        if( empls->data[i * DFS_END + SEX] == MAN)
        {
            empls->age_mid_mn += empls->data[i * DFS_END + AGE];
            empls_count_mn++;
        }
        else
        {
            empls->age_mid_wn += empls->data[i * DFS_END + AGE];
            empls_count_wn++;
        }
    }
    empls->age_mid_mn /= empls_count_mn;
    empls->age_mid_wn /= empls_count_wn;
}

void outData()
{
    sEmployees empls = EMPLOYEES;
    int i = 0;

    mf_OpenFile(empls->result_file_name, "w", &(empls->empls_fl));
    if( empls->empls_fl == NULL ) exit(0);

    for(i = 0; i < empls->empls_count; i++)
    {
        fprintf(empls->empls_fl, "%s ", (empls->surnames) + i                  * empls->surname_max_len);
        fprintf(empls->empls_fl, "%s ", (empls->names)    +
                                         empls->data[i * DFS_END + NAME_INDEX] * empls->name_max_len);
        if( empls->data[i * DFS_END + SEX] == MAN )
            fprintf(empls->empls_fl, "%s ", "чол");
        else
            fprintf(empls->empls_fl, "%s ", "жін");
        fprintf(empls->empls_fl, "%d ", (empls->data[i * DFS_END + AGE]));
        if( empls->data[i * DFS_END + EMPL] )
            fprintf(empls->empls_fl, "%s", "так");
        else
            fprintf(empls->empls_fl, "%s", "ні");
        fputs("\n", empls->empls_fl);
    }
    fprintf(empls->empls_fl, "AGE_MIN:       %d\n",   empls->age_min);
    fprintf(empls->empls_fl, "AGE_MAX:       %d\n",   empls->age_max);
    fprintf(empls->empls_fl, "MID_AGE_MAN:   %.1f\n", empls->age_mid_mn);
    fprintf(empls->empls_fl, "MID_AGE_WOMAN: %.1f\n", empls->age_mid_wn);
    fclose(empls->empls_fl);

    puts("--------------------------------------------");
    puts("прізвище - ім'я - стать - вік - співробітник");
    puts("--------------------------------------------");
    for(i = 0; i < empls->empls_count; i++)
    {
        printf("%s ", (empls->surnames) + i                                     * empls->surname_max_len);
        printf("%s ", (empls->names)    + empls->data[i * DFS_END + NAME_INDEX] * empls->name_max_len);
        if( empls->data[i * DFS_END + SEX] == MAN )
            printf("%s ", "чол");
        else
            printf("%s ", "жін");
        printf("%d ", (empls->data[i * DFS_END + AGE]));
        if( empls->data[i * DFS_END + EMPL] )
            printf("%s ", "так");
        else
            printf("%s ", "ні");
        puts("");
    }
    puts("--------------------------------------------");
    printf("AGE_MIN:       %d\n",   empls->age_min);
    printf("AGE_MAX:       %d\n",   empls->age_max);
    printf("MID_AGE_MAN:   %.1f\n", empls->age_mid_mn);
    printf("MID_AGE_WOMAN: %.1f\n", empls->age_mid_wn);
    puts("--------------------------------------------");
}

void empls_init(sEmployees empls)
{
    empls->empls_count     = EMPLS_COUNT;
    empls->surname_max_len = SURNAME_MAX_LEN * 2 + 1; //*2 - для багатобайтних символів
    empls->name_max_len    = NAME_MAX_LEN * 2 + 1;    //*2 - для багатобайтних символів
    empls->age_start_1     = AGE_START_1;
    empls->age_start_2     = AGE_START_2;
    empls->age_end_1       = AGE_END_1;
    empls->age_end_2       = AGE_END_2;

    empls->surnames   = (char *)calloc(empls->empls_count * empls->surname_max_len, sizeof(char));
    empls->names      = (char *)calloc(empls->empls_count * empls->name_max_len   , sizeof(char));
    empls->data       = (int  *)calloc(empls->empls_count * DFS_END               , sizeof(int));
    empls->age_min    = 0;
    empls->age_max    = 0;
    empls->age_mid_mn = 0;
    empls->age_mid_wn = 0;

    empls->surnames_file_name = (char *)calloc(strlen(SURNAMES_FILE) + 1, sizeof(char));
    empls->names_file_name    = (char *)calloc(strlen(NAMES_FILE)    + 1, sizeof(char));
    empls->result_file_name   = (char *)calloc(strlen(RESULT_FILE)   + 1, sizeof(char));

    strcpy(empls->surnames_file_name, SURNAMES_FILE);
    strcpy(empls->names_file_name, NAMES_FILE);
    strcpy(empls->result_file_name, RESULT_FILE);

    empls->readFiles  = readFiles;
    empls->fixSex     = fixSex;
    empls->changeSur  = changeSur;
    empls->fixName    = fixName;
    empls->fixAge     = fixAge;
    empls->fixRange   = fixRange;
    empls->filterAppl = filterAppl;
    empls->midAge     = midAge;
    empls->outData    = outData;
    empls->free       = empls_free;
    EMPLOYEES = empls;
}

void empls_free()
{
    sEmployees empls = EMPLOYEES;

    free(empls->surnames);
    free(empls->names);
    free(empls->data);
    free(empls->surnames_file_name);
    free(empls->names_file_name);
    free(empls->result_file_name);

    EMPLOYEES = NULL;
}

//----------------------------------------------------------------------------//
//    OTHER FUNCTIONS                                                         //
//----------------------------------------------------------------------------//
void mf_OpenFile(char * file_name, char * file_mode, FILE ** file_ptr_addr)
{
    *file_ptr_addr = fopen(file_name, file_mode);

    if( *file_ptr_addr )
    {
        rewind(*file_ptr_addr);
        return;
    }

    switch( *file_mode )
    {
        case 'r':
            printf("FILE %s DOES NOT EXIST!\n", file_name);
            break;
        case 'a':
        case 'w':
            printf("CAN NOT OPEN OR CREATE FILE %s!\n", file_name);
            break;
    }
}

int mf_Rnd(int range_min_value, int range_max_value)
{
    return (double)rand() / 32767 * (range_max_value - range_min_value) + range_min_value + 0.5;
}

void mf_StrCut(char * string, char * string_cut)
{
    char * string_cut_pos;

    if( (string_cut_pos = strstr(string, string_cut)) )
        *string_cut_pos = '\0';
}

bool mf_StrRplEnd(char * string, char * string_end, char * string_rpl)
{
    int str_len     = strlen(string);
    int str_end_len = strlen(string_end);

    if( str_len < str_end_len ) return false;
    if( strcmp(string + str_len - str_end_len, string_end) != 0 ) return false;

    strcpy(string + str_len - str_end_len, string_rpl);
    return true;
}

int mf_ReadFile(char * file_name, char * array, int array_size_N, int array_size_M)
{
    FILE * input_file = NULL;
    int counter       = 0;

    mf_OpenFile(file_name, "r", &input_file);
    if( input_file == NULL ) return -1;
    for(counter = 0;
        counter < array_size_N && fgets(array + counter * array_size_M, array_size_M, input_file);
        counter++)
        mf_StrCut(array + counter * array_size_M, "\n");
    fclose(input_file);
    return counter;
}
