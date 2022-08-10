#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

    char names[5][10];  // name storage
    int count=0;        // input counter
    char temp[10];      // temp string
    int i, j;      

    while(scanf("%s",&names[count]) != EOF){    //read inputs
        count++;
    }

    for (i = 0; i < count - 1 ; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(names[i], names[j]) > 0) 
            {
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }

    for (i = 0; i < count; i++) {
        printf("%s\n",names[i]); 
    }
    return 0;
}