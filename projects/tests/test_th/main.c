#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*
https://msdn.microsoft.com/en-us/library/windows/desktop/ms682516(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/ms682453(v=vs.85).aspx
*/

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void MyThreadFunction(int * counter)
{
    //int counter = 0;
    while(counter < 20)
    {
        printf("IT`S WORK!\n");
        Sleep(500);

        counter++;
    }
}

int main(void) {
    int threadId     = 0;
    int thr_counter  = 0;

    HANDLE thread = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size
            MyThreadFunction,       // thread function name
            thr_counter, 			// argument to thread function
            0,                      // use default creation flags
            &threadId);   			// returns the thread identifier

    int counter = 0;
    while(counter < 20)
    {
        printf("IT`S the main thread!\n");
        Sleep(500);

        counter++;
    }

    WaitForSingleObject(thread, INFINITE);

    CloseHandle(thread);
    return 0;
}
