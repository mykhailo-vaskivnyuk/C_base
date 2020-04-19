#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <conio.h>

void * someFunc(void *);

int main ()
{
    //char * par = "DONE";
    unsigned int par = 0; //1000000;

    pthread_t proc = NULL;
    pthread_create(&proc, NULL, someFunc, &par);
    //while( par < 1000000)
    //    printf("HELLO %u\n", par);
    //while( par < 1000000)
    //    printf("HELLO %u\n", par);
    //scanf("%d", &par);
    while( par != 1 )
    {
        if( getch() == '\r') par = 2;
        else par = 1;
    }
    pthread_join(proc, NULL);



    return 0;
}

void * someFunc(void * par)
{
    int count = 0; //*(int *)par;
    int * i = (int *)par;

    //*i = 0;

    //while( (*i)++ < count );
    //    if( getch() == 'q' ) break;

    while ( *(int*)par != 1 )
    {
        system("cls");
        printf("HELLO %d\n", count++);
        if( *(int*)par == 2 )
        {
            count = 0;
            *(int*)par = 0;
        }
    }

    *(int*)par = 100;

    return NULL; //(void *)&i; //par;
}

void goTimer()
{
    //unsigned int x_hours=0;
    unsigned int x_minutes=0;
    unsigned int x_seconds=0;
    unsigned int x_milliseconds=0;
    unsigned int count_down_time_in_secs=0,time_left=0; //totaltime=0

    clock_t x_startTime,x_countTime;
    count_down_time_in_secs=10;  // 1 minute is 60, 1 hour is 3600


    x_startTime=clock();  // start clock
    time_left=count_down_time_in_secs-x_seconds;   // update timer

    while (time_left>0)
    {
        x_countTime=clock(); // update timer difference
        x_milliseconds=x_countTime-x_startTime;
        x_seconds=(x_milliseconds/(CLOCKS_PER_SEC))-(x_minutes*60);
        x_minutes=(x_milliseconds/(CLOCKS_PER_SEC))/60;
        //x_hours=x_minutes/60;

        time_left=count_down_time_in_secs-x_seconds; // subtract to get difference

        system("cls");
        printf( "\nYou have %d seconds left ( %d ) count down timer by TopCoder",
                                    time_left, count_down_time_in_secs);
    }

    printf( "\n\n\nTime's out\n\n\n");
}
