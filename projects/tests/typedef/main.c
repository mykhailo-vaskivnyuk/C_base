#include <stdio.h>

FILE * openFile(char *, FILE **);
void rwFile(void);

int main(void)
{
    //rwFile();
    struct test
    {
        int test;
    };

    struct test new_test;
    struct test * try_test = &new_test;


    try_test->test = 100;
    printf("%d %d\n", try_test->test, new_test.test);

    return 0;
}

void rwFile(void)
{
    FILE * test_file = NULL;
    char * file_name = "test_file.dat";
    int number = 0;

    openFile(file_name, &test_file);
    number = 255;
    fwrite(&number, sizeof(int), 1, test_file);
    fflush(test_file);
    number = 0;
    rewind(test_file);
    fread(&number, sizeof(int), 1, test_file);
    printf("NUMBER %d\n", number);
}

FILE * openFile(char * file_name, FILE ** file_ptr_adrr)
{
    FILE * file_ptr;
    *file_ptr_adrr = fopen(file_name, "w+");
    file_ptr = *file_ptr_adrr;
    return file_ptr;
}

/*----------- test_part_7_5 ----------------------------------------------------------
    int contacts_count = 0;
    char c = '\0';
    FILE * input_file = NULL;
    FILE * contacts_file = NULL;
    char * input_file_name = "contacts.txt";
    char * contacts_file_nsme = "contacts.dat";
    struct contact
    {
        char first_name[15];
        char last_name[20];
        float age;
        int phone;
    } * contacts_ptr = NULL;
    struct contact contact_tmp_1;
    struct contact contact_tmp_2;
    size_t contact_data_size = sizeof(struct contact);
//------------------------------------------------------------------------------------
//      записуємо контакти в файл contacts.dat, джерелом даних є файл contacts.txt
//------------------------------------------------------------------------------------
    openFile(input_file_name, "r", &input_file);
    if( !input_file ) return 0;

    while( (c = getc(input_file)) != EOF )
        if( c == '\n' ) contacts_count++;

    contacts_ptr = (struct contact *)malloc(contacts_count * sizeof(struct contact));

    openFile(contacts_file_nsme, "wb+", &contacts_file);
    if( !contacts_file )
    {
        fclose(input_file);
        return 0;
    }

    rewind(input_file);
    for(i = 0; i < contacts_count; i++ )
    {
        fscanf(input_file, "%s%s%f%d",  contacts_ptr[i].first_name,
                                        contacts_ptr[i].last_name,
                                        &contacts_ptr[i].age,
                                        &contacts_ptr[i].phone);
        printf("%15s %20s %10.2f %8d\n",
                        contacts_ptr[i].first_name,
                        contacts_ptr[i].last_name,
                        contacts_ptr[i].age,
                        contacts_ptr[i].phone);
        fwrite(&contacts_ptr[i], sizeof(struct contact), 1, contacts_file);
    }

    fflush(contacts_file);
    free(contacts_ptr);
//------------------------------------------------------------------------------------

    for(i = 0; i < contacts_count / 2; i++)
    {
        fseek(contacts_file, contact_data_size * i, SEEK_SET);
        fread(&contact_tmp_1, contact_data_size, 1, contacts_file);
        fseek(contacts_file, -contact_data_size * (i + 1), SEEK_END);
        fread(&contact_tmp_2, contact_data_size, 1, contacts_file);

        fseek(contacts_file, contact_data_size * i, SEEK_SET);
        fwrite(&contact_tmp_2, contact_data_size, 1, contacts_file);
        fflush(contacts_file);
        fseek(contacts_file, -contact_data_size * (i + 1), SEEK_END);
        fwrite(&contact_tmp_1, contact_data_size, 1, contacts_file);
        fflush(contacts_file);
    }

    rewind(contacts_file);
    printf("\n\n");
    for(i = 0; i < contacts_count; i++)
    {
        fread(&contact_tmp_1, contact_data_size, 1, contacts_file);
        printf("%15s %20s %10.2f %8d\n",
                    contact_tmp_1.first_name,
                    contact_tmp_1.last_name,
                    contact_tmp_1.age,
                    contact_tmp_1.phone);
    }
*/
