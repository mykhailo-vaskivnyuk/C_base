/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 7. Файли з довільним доступом.
 * Частина 5. Підсумкове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 03.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Відкрити в режимі запису двійковий файл “contacts.dat”,
   до якого в циклі програми внести наступні дані (хоча б 10-11 записів):
   а) прізвище та ім’я особи;
   б) вік особи (дійсне число у форматі Р.М, де Р - кількість років, М - кількість місяців);
   в) телефон (6-значне ціле число).
2. По закінченні запису - вивести весь перелік контактів на екран (з метою контролю);
3. Організуйте “дзеркальну” перестановку записів - перший поміняти з останнім,
   другий - з передостаннім і т.д. Результати перестановки записати в початковий
   двійковий файл (допоміжний файл - не відкривати!!!);
4. По закінченні перестановки - прочитати з файлу результат,
   переконатись в коректності проведених перестановок, а також що жоден запис не втрачено.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_LEN 39

void openFile(char *, char *, FILE **);
void printContacts(FILE *);

struct contact
{
    char first_name[11];
    char last_name[11];
    float age;
    int phone;
};

int main(void)
{
    //вважаємо наступне:
    //вхідний файл має чітко заданий формат
/*
Mykhailo    Vaskivnyuk 40.03 123456
Sasha       Petrov     23.11 438588
Sergij      Ogorodnik  20.08 347211
Vasya       Pushkin    33.10 559380
Svitlana    Kovtun     40.02 437665
Oleksandr   Tsymbal    15.07 212233
Iryna       Chemerys   35.06 544566
Oliga       Olinich    17.05 782312
Oksana      Antonova   27.08 543221
Dmytro      Pryjmak    29.04 112233
Yurij       Mityushkin 30.00 859112
*/
    //вхідний файл має мінімум один запис
    int contacts_count = 0;
    FILE * input_file = NULL;
    FILE * contacts_file = NULL;
    char * input_file_name = "contacts.txt";
    char * contacts_file_nsme = "contacts.dat";
    struct contact contact;
    struct contact contact_tmp;
    size_t contact_data_size = sizeof(struct contact);
    char contact_str[MAX_STR_LEN + 1] = "";
    int i = 0;
//------------------------------------------------------------------------------------
//  записуємо контакти в файл contacts.dat, джерелом даних є файл contacts.txt
//------------------------------------------------------------------------------------
    openFile(input_file_name, "r", &input_file);
    if( !input_file ) return 0;

    openFile(contacts_file_nsme, "wb+", &contacts_file);
    if( !contacts_file )
    {
        fclose(input_file);
        return 0;
    }

    while( fgets(contact_str, MAX_STR_LEN + 1, input_file) != NULL)
    {
        sscanf(contact_str, "%s%s%f%d",  contact.first_name,
                                         contact.last_name,
                                        &contact.age,
                                        &contact.phone);
        fwrite(&contact, contact_data_size, 1, contacts_file);
        contacts_count++;
    }
    //fflush(contacts_file);
    fclose(input_file);
//------------------------------------------------------------------------------------
//  виводимо зміст contacts.dat на екран
//------------------------------------------------------------------------------------
    puts("\n-------------------- CONTACTS BEFORE --------------------\n");
    printContacts(contacts_file);
    printf("\n");
//------------------------------------------------------------------------------------
//  виконуємо дзеркальну перестановку в contacts.dat
//------------------------------------------------------------------------------------
    for(i = 0; i < contacts_count / 2; i++)
    {
        //------- READ -------
        fseek(contacts_file, contact_data_size * i, SEEK_SET);
        fread(&contact, contact_data_size, 1, contacts_file);

        fseek(contacts_file, -contact_data_size * (i + 1), SEEK_END);
        fread(&contact_tmp, contact_data_size, 1, contacts_file);

        //------- WRITE ------
        fseek(contacts_file, contact_data_size * i, SEEK_SET);
        fwrite(&contact_tmp, contact_data_size, 1, contacts_file);
        //fflush(contacts_file);

        fseek(contacts_file, -contact_data_size * (i + 1), SEEK_END);
        fwrite(&contact, contact_data_size, 1, contacts_file);
        //fflush(contacts_file);
    }
//------------------------------------------------------------------------------------
//  виводимо змінений contacts.dat на екран
//------------------------------------------------------------------------------------
    puts("\n-------------------- CONTACTS AFTER ---------------------\n");
    printContacts(contacts_file);
    printf("\n");
    fclose(contacts_file);

    return 0;
}
/*************************************************************************************
    FUNCTIONS
*************************************************************************************/
void openFile(char * file_name, char * file_mode, FILE ** file_ptr_addr)
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
        case 'w':
            printf("CAN NOT OPEN OR CREATE FILE %s !\n", file_name);
            break;
    }
}
//------------------------------------------------------------------------------
void printContacts(FILE * contacts_file)
{
    struct contact contact;

    rewind(contacts_file);
    while( fread(&contact, sizeof(struct contact), 1, contacts_file) )
        printf("%-11s %-11s %5.2f %6d\n",
                contact.first_name,
                contact.last_name,
                contact.age,
                contact.phone);
}
