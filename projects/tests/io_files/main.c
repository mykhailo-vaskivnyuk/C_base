#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void func_a(void);
void func_b(void);
void func_c(void);
void func_d(void);
void func_e(void);

void printFileStruct(FILE *);

int main(void)
{

    func_e();

    return 0;
}

void func_b(void)
{
    FILE * fl = NULL;
    char bf[40] = {};
    char *sng = "1234 1234 1234 12345";

    fl = fopen("test.txt", "w");
    setbuf(fl, bf);
    printf("%d %d", sizeof(char), strlen(sng));
    fwrite(sng, sizeof(char), strlen(sng), fl);
    //fflush(fl);
    fclose(fl);

}

void func_a(void)
{
    FILE * f = NULL;
    char string[80 + 1] = "";
    char * ptr = NULL;

    f = fopen("test_file.txt", "r");
    fgets(string, 80, f);
    //fflush(NULL);
    if( (ptr = strstr(string, "\n")) )
       *ptr = '\0';
    //fflush(NULL);
    fputs(string, stdout);
}

void func_c()
{
    FILE * fl      = NULL;
    char   bf[20]  = "";
    char   sng[20] = "5555555555";
    int    bufsize = 20;

    fl = fopen("test.txt", "wb+");
    setvbuf(fl, bf, _IOFBF, bufsize);
    fwrite("1111111111", 10, 1, fl);
    fwrite("2222222222", 10, 1, fl);
    fwrite("3333333333", 10, 1, fl);
    fflush(fl);
    memset(bf, 65, 20);
    fseek(fl, 0, SEEK_SET);
    fwrite("44444", 5, 1, fl);
    //(fl);
    fread(sng, 1, 2, fl);
    fclose(fl);
    return;

    fwrite(sng, strlen(sng) + 0, 1, fl);
    printFileStruct(fl);

    fwrite("11111", 5 + 0, 1, fl);
    printFileStruct(fl);
    rewind(fl);
    fflush(fl);

    memset(sng, 0, 20);
    fread(sng, 5, 1, fl);
    printf("%s", sng);
}

void printFileStruct(FILE * fl)
{
    printf("_base     (* char): %s\n", fl->_base);
    printf("_bufsiz   (  int) : %d\n", fl->_bufsiz);
    printf("_charbuf  (  int) : %d\n", fl->_charbuf);
    printf("_cnt      (  int) : %d\n", fl->_cnt);
    printf("_file     (  int) : %d\n", fl->_file);
    printf("_flag     (  int) : %d\n", fl->_flag);
    printf("_ptr      (* char): %s\n", fl->_ptr);
    printf("_tmpfname (* char): %s\n", fl->_tmpfname);
    puts("\0");
}

void func_d(void)
{
    char str[20] = "";
    scanf("%s", str);
}

void func_e(void)
{
    int i = 0;
    int j = 0;
    char str[16] = "";
    char str_in[16] = "";

    setbuf(stdin, str);

    for(i = 0; i < 1000; i++)
    {
        for(j = 0; j < 2; j++)
        {
            system("cls");
            printf("%d\n", i * 2 + j);

        }
        fwrite("\n", 1, 1, stdin);
        fflush(stdout);
        fread(str_in, 1, 1, stdin);

        if( *str == 'q' ) return;
    }
}
