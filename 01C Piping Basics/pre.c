#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

    char names[5][10];  // name storage
    double gpa[5];      // gpa storage
    int count=0;        // input counter   

    while(scanf("%s %lf",&names[count],&gpa[count]) != EOF){    //read inputs
        count++;
    }

    for(int i=0;i<count;i++){
        if(gpa[i]>=3.0){                //if gpa >= 3.0 print name
            printf("%s\n",names[i]);
        }
    }
return 0;
}