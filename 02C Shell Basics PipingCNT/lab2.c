//Jason McKinnerney
//Project 2 - Operating Systems

//Write a small shell - called shhh - that has the
//following capabilities:
//
//1. Can execute a command with the accompanying arguments.
//2. Recognize multiple pipe requests and handle them.
//3. Recognize redirection requests and handle them.
//4. Type "exit" to quit the shhh shell.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h> 
#define READ 0
#define WRITE 1

main()

{

char *path, *argv[20], buf[80], n, *p;

int m, status, inword, continu;



while(1) {



inword = 0;

p = buf;

m = 0;

continu=0;



printf( "\nshhh> ");

while ( ( n = getchar() ) != '\n'  || continu ) {

	if ( n ==  ' ' ) {

	    if ( inword ) {

		inword = 0;

		*p++ = 0;

	    }

	}

	else if ( n == '\n' ) continu = 0;

	else if ( n == '\\' && !inword ) continu = 1;

	else {

	    if ( !inword ) {

		 inword = 1;

		 argv[m++] = p;

		 *p++ = n;

	     }

	     else

		 *p++ = n;

	}

}

*p++ = 0;

argv[m] = 0;


// No need to change anything above. Your program will continue //from here

if ( strcmp(argv[0],"exit") == 0 ) exit (0); //exit if first command is exit



        // Set variables for processing
        char *inPath;
        char *outPath;

        int arguments[20] = {0};
        int rightPipe[2];
        int leftPipe[2];

        int inFlag = 0;
        int outFlag = 0;

        int count = 0;
        int pipes = 0;
        int pid = 0;
        int index = 0;


     // Start of Preprocessing
        while(argv[count] != 0) {					// Handle pipes
            if( strcmp( argv[count], "|") == 0) {
                argv[count] = 0;
                arguments[pipes + 1] = count + 1;
                ++pipes;
                }
            else if( strcmp(argv[count], "<" ) == 0) {	// Handle input redirection
                inPath = strdup(argv[count + 1]);
                argv[count] = 0;
                argv[count + 1] = 0;
                inFlag = 1;
                count++;
                }
            else if( strcmp(argv[count], ">" ) == 0) {	// Handle output redirection
                outPath = strdup(argv[count + 1]);
                argv[count] = 0;
                argv[count + 1] = 0;
                outFlag = 1;
                count++;
                }
            else
                arguments[count] = count;
            
            ++count;
        }
        
		// End of preprocessing


        //Loop through pipes
        for(index; index <= pipes; index++) {		
            if( (pipes > 0) && (index != pipes))	// if (there are pipe && this is not the last process) create a right pipe
                pipe(rightPipe); 
            
            // execute commands
            switch (pid = fork()) {
                case -1:
                    //error
                    perror("Fork, you are a big failure and I am dissapointed in you.");
                    break;
                case 0:
                    if ((index == 0) && (inFlag == 1)) {			// read input file if exists
                        int inFile = open(inPath, O_RDONLY, 0400);
                        if(inFile == -1) {
                            perror("The input file has failed!\n");
                            return(EXIT_FAILURE);
                        }
                        close(READ);
                        dup(inFile);
                        close(inFile);
                    }
                    
                    if ((index == pipes) && (outFlag == 1)) {		// Output file 
                        int outFile = open(outPath, O_WRONLY | O_CREAT, 0755);
                        if(outFile < 0) {
                            perror("The output file has failed!\n");
                            return(EXIT_FAILURE);
                        }
                        close(WRITE);
                        dup(outFile);
                        close(outFile);
                    }
                    
                    //manage pipes
                    if (pipes > 0) {
                        if (index == 0) {               // First pipe creation
                            close(WRITE);
                            dup(rightPipe[WRITE]);
                            close(rightPipe[WRITE]);
                            close(rightPipe[READ]);
                            }
                        else if ( index < pipes){       // If more pipes need to be created
                            close(READ);
                            dup(leftPipe[READ]);
                            close(leftPipe[READ]);
                            close(leftPipe[WRITE]);
                            close(WRITE);
                            dup(rightPipe[WRITE]);
                            close(rightPipe[READ]);
                            close(rightPipe[WRITE]);
                            }
                        else{                           // Final pipe , don't create right pipe
                            close(READ);
                            dup(leftPipe[READ]);
                            close(leftPipe[READ]);
                            close(leftPipe[WRITE]);
                        }
                    }
                    execvp(argv[arguments[index]], &argv[arguments[index]]);
                    perror("The command failed\n");
                    break;
                default:
                    // parent process
                    if (index > 0) {
                        close(leftPipe[READ]);
                        close(leftPipe[WRITE]);
                    }
                    
                    leftPipe[READ] = rightPipe[READ];
                    leftPipe[WRITE] = rightPipe[WRITE];
        
                    wait(&status);
                    break;
            }
        }
    }
    
    return 0;
}