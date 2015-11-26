#include <stdio.h>
#include "regexp.h"
#include "tokenizer.h"
#include <string.h>

#define DEBUG 0
#define MAX_LINE    1024
/*
 Ian Hammerstrom
 June 27th, 2015
 fref is a utility that will search through one or more files and report any lines in those files that contain a string matching a specified regular expression.
 */

int main(int argc, char *argv[]){
    int i=0, lineNum=0;
    char line[MAX_LINE];
    int lineLength = (sizeof(line)/sizeof(char)), count=0, decrem=0;
    char **tokens;
    
/*#if DEBUF
    printf("gets to point 0\n");
#endif*/
    if(argc<3){//Message displayed if less than 3 arguments are passed.
        //printf("\nNeeds atleast 3 arguments (including \"./fref\")\n");
        printf("fref [regular expression] [file name]\n");
        printf("fref is a utility that will search through one or more files and report any lines in those files that contain a string matching a specified regular expression.\n\n");
        printf("Please enter: [regular expression] [file name]\n");
        fgets(line, MAX_LINE, stdin);
        if(line[strlen(line)-1]=='\n'){//sometimes there's no \n at the end of the file and it cuts off last character
            line[strlen(line)-1]='\0';
        }
        tokens = gettokens(line);
        while(tokens[count]) count++;
     

        decrem = 1;
        i=1;

    }else{
        tokens=argv;
        count=argc;
        i=2;
    }

/*#if DEBUG
        printf("gets to point 1\n");
#endif*/
    for(; i< count; i++){// i=i clears GCC warning "statement with no effect"
        FILE *inFile = fopen(tokens[i], "r"); //Attempts to open file.
        if (inFile ==NULL){
            printf("File \"%s\" not found.\n", tokens[i]);
            return 0;
        }
        printf("Succesfully opened file \"%s\"\n", tokens[i]);
/*#if DEBUG
        printf("gets to point 2\n");
#endif*/
        while (fgets(line, lineLength, inFile)){//If the RegExp. is found in a line in the file, the line is printed to the console.
/*#if DEBUG
            printf("gets to point 3\n");
#endif*/
            lineNum++;
            if (match(tokens[1-decrem], line)){
                printf("%s:%d %s",tokens[i-decrem], lineNum, line);
            }
        }
/*#if DEBUG
        printf("gets to point 4\n");
#endif*/
        
        fclose(inFile);
    }
    
    
    return 0;
}