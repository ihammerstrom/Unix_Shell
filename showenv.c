#include "showenv.h"

#define DEBUG 0

#define MAX_LINE    1024
#define MAX_TEMP    256

/*
 Ian Hammerstrom
 July 17th, 2015
 CSCI 352 - Showenv
 
 Prints any environment variables that begin with with the tokens passed in from the command line or stdin.
 */

int contains(char *temp, char *environment);

int main(int argc, char *argv[]){
    extern char ** environ;

    char line[MAX_LINE];
    char **tokens;
    int i=0, j=0, found =0;


    if(argc==1){ //if no command line arguments, use stdin
        printf("Enter the beginnings or more of environment variables you'd like to see: \n");
        fgets(line, MAX_LINE, stdin);
        if(line[strlen(line)-1]=='\n'){//sometimes there's no \n at the end of the file and it cuts off last character
            line[strlen(line)-1]='\0';
        }

        tokens = gettokens(line);

    }else{ //command line arguments 
        tokens=argv;
        i=1;
    }

    for(; tokens[i]; i++){//looks through all tokens(yes, I know: i=i, but this gets rid of a "statement with no effect" warning
        for(j=0; environ[j]; j++){ //looks through all environment variables
            if(contains(tokens[i], environ[j])){
                printf("%s\n", environ[j]);
                found=1;
            }
        }
        if(!found){
            printf("Didn't find any environment variables beginning with: %s\n", tokens[i]);
        }
        found=0;
    }

    return 0;
}

//if the string temp is contained in the string environment returns 1, 0 otherwise
int contains(char *temp, char *environment){
    int i=0;

    for(i=0; temp[i] && environment[i]; i++){

        if (environment[i]!=toupper(temp[i])){
            return 0;
        }
    }
    return 1;

}