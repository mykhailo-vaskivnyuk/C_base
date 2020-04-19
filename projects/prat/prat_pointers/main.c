#include <stdio.h>

int main(void)
{
    printf("Hello World!\n");
    //дослідити (int*)pointer
        //чи можна *char to *int ?
    //дослідити *function
    //дослідити * = NULL
    void ToUpper (char *);
    void (*pf)(char *); //pf - указатель на функцию
    void *pf(char *); //pf - функция, возвращающая указатель
    void ToUpper(char *);
    void ToLower(char *);
    int round(double);
    void (*pf)(char *);

    pf = ToUpper; //допу стимо , ToUpp er - адр е с функции
    pf = ToLower; //допу стимо , T o Lower - адр е с функции
    pf = round; //11 недопустимо , round - неподходящий тип ф ункции
    pf = ToLower( );//1 1 недопустимо , To Lower ( ) не я вля ется адр е сом

    char mis[ ] = "Nina Metier";
    pf = ToUpper;
    (*pf)(mis); //применить T o Upp er к мас сиву mi s ( синтакси с 1 )
    pf = ToLower;
    pf(mis); //применить To Lower к мас сиву mi s ( синтакси с 2 )

    void show( void (*fp)(char *), char *str ) ;
    show( ToLower, mis ); /* show ( ) исполь зуе т функцию To Lower ( ) : fp = ToLower */
    show( pf, mis ); /* s how ( ) и спол ь з у е т функцию , на ко тор ую указыв а е т p f : fp = p f * /

            void s how ( void ( * fp ) ( char * ) , char * s tr )
            {
            ( * fp ) ( s tr ) ;
            puts ( s tr ) ;
            / * примени т ь выбр анную функцию к s tr * /
            / * выв е с ти р е зуль тат *



    return 0;
}

