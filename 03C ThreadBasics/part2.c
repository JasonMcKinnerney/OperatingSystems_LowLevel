//Jason McKinnerney
//lab3 part1
//Write program with threads with mutual exclusion

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


void looperA (char c);


pthread_mutex_t mutex;
pthread_cond_t waitA;
pthread_cond_t waitB;

int main()
{
    // starting values
    setup.iterations = 10;
    setup.lines = 5;
    
    // create threads
    pthread_t thread1, thread2;
    
    // initialize threads
    pthread_create(&thread1, NULL, (void *(*)(void *)) looperA, (void*) 'A');
    pthread_create(&thread2, NULL, (void *(*)(void *)) looperA, (void*) 'B');

    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    
    printf("complete");
    
    pthread_exit(0);
}


void looperA(char c)
{
    // initialize variables
    int iter = 1;
    int x;
    int y;
    
    while(iter <= setup.iterations)
    {   
        pthread_mutex_lock(&mutex);
        for (x=0; x < setup.lines; x++ ) {
        printf("%d: ", iter);
        for (y=0; y < 10; y++) {
            printf("%c",c);
        }
        printf("\n");
        }
        printf("\n");
        iter++;
        pthread_mutex_unlock(&mutex);
    
        sleep(1);
    }
}
    
