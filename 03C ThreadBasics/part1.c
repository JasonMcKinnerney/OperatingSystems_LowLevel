//Jason McKinnerney
//lab3 part1
//Write program with threads without mutual exclusion

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>


struct loopValues
{
    int iterations;
    int lines;
};

// create instance of struct
struct loopValues setup;

// student function
void looper (char c);

int main()
{
    // starting values
    setup.iterations = 10;
    setup.lines = 5;
    
    // create threads
    pthread_t thread1, thread2;
    
    // initialize threads
    pthread_create(&thread1, NULL, (void *(*)(void *)) looper, (void*) 'A');
    pthread_create(&thread2, NULL, (void *(*)(void *)) looper, (void*) 'B');

    // have threads wait for completion of other threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    
    printf("complete");
    
    pthread_exit(0);
}


void looper(char c)
{
    // initialize variables
    int iter = 1;
    int x;
    int y;
    
    while(iter <= setup.iterations)
    {
        for (x=0; x < setup.lines; x++ ) {
        printf("%d: ", iter);
        for (y=0; y < 10; y++) {
            printf("%c",c);
        }
        printf("\n");
        }
        printf("\n");
        iter++;
    
        sleep(1);
    }
}
    

