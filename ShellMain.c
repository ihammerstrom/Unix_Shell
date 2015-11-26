#include "ShellMain.h"

#define MAX_LINE    1024
#define TRUE 1
#define UTILITY_MAX 32


/*
 Ian Hammerstrom
 July 18th, 2015
 ShellMain is a command line interpreter (CLI) that includes the utilities located in /bin/ 
 as well as it's originating path, which include fref and showenv.

 */


int execute(char *path, char *process, char **tokens);
void IORedirect(char **tokens);
char **cleanIOTokens(char **tokens);
char **addSpaceCarots(char **tokens);

int main (int argc, char** argv) {
    char line[MAX_LINE];
    char **tokens;
    printf("Starting in: ");
    char *beginningPath = pwd();

    char pathUtility[strlen("/bin/")+UTILITY_MAX];
    strcpy(pathUtility, "/bin/");

    // get a line from stdin and get the tokens
    printf("> ");
    while (fgets(line, MAX_LINE, stdin)) {

        while(strcmp(line, "\n")==0){
            printf("$> ");
            fgets(line, MAX_LINE, stdin);
        }
        // remove the '\n' from the end of the line
        line[strlen(line)-1] = '\0';

        
        // get and display the tokens in line
        while(strlen(line)==0){
            printf(">\n");
            fgets(line, MAX_LINE, stdin);
        }

        //makes tokens from line
        tokens = gettokens(line);

        //tokens before clean
        /*printf("tokens before clean: \n");
        for (i=0; tokens[i]; i++)
            printf("token %d is '%s'\n", i, tokens[i]);*/

        //adds spaces between carots and files, ex: <input.txt --> < input.txt
        tokens = addSpaceCarots(tokens);


        //redirects IO if a carot is found
        IORedirect(tokens);

        //cleans the IO redirectors from tokens
        tokens = cleanIOTokens(tokens);  

        /*printf("tokens after clean: \n");
        for (i=0; tokens[i]; i++)
            printf("token %d is '%s'\n", i, tokens[i]);*/


        //chooses what to do based on first token
        if(strcmp(tokens[0], "pwd")==0){
               pwd();

        }else if(strcmp(tokens[0], "exit")==0){
            return EXIT_SUCCESS;

        }else if(strcmp(tokens[0], "cd")==0){
            cd(tokens[1]);

        }else if(strcmp(tokens[0], "fref")==0){
            execute(beginningPath, "/fref", tokens);

        }else if(strcmp(tokens[0], "showenv")==0){
            execute(beginningPath, "/showenv", tokens);

        }else{
            execute(pathUtility, tokens[0], tokens);
        }

        //cleanup section
        freopen ("/dev/tty", "a", stdout);//redirect stdout back to terminal, not very portable.
        freopen("/dev/tty", "r", stdin);//redirect stdin back to terminal, not very portable.
        free(tokens);

        printf("$> ");
    }

    return 0;

}


//calls execv on a utility at a certain path and passes it tokens
int execute(char *path, char *process, char **tokens){
    pid_t pid;
    int status;
    pid = fork();

    if(pid==0){//child process

        strcat(path, process);
        execv(path, tokens);

        //Reaches here if execv failes
        printf("Could not execute: %s\n", process);

        exit(EXIT_FAILURE);

    }else if(pid<0){
        printf("fork() failed\n");
        exit(EXIT_FAILURE);
    }else{ //parent process

        wait(&status);
        return 0;
    }
}

//redirects IO if a carot is found in tokens
void IORedirect(char **tokens){
    int i=0;
    for(i=0; tokens[i]; i++){
        if(strcmp(tokens[i], ">")==0 && tokens[i+1]){
            freopen(tokens[i+1], "w", stdout);
        }else if(strcmp(tokens[i], "<")==0 && tokens[i+1]){
            if(!freopen(tokens[i+1], "r", stdin)){
                printf("Couldn't find file: %s\n", tokens[i+1]);
            }
        }
    }
}

//clears tokens of all IO redirectors
char **cleanIOTokens(char **tokens){
    int i=0;
    int numTokens=0;

    while(tokens[i]){
        if(strcmp(tokens[i], "<")==0 || strcmp(tokens[i], ">")==0){
            i+=2;

        }else{
            i++;
            numTokens++;
        }
    }
    char **newTokens = (char **)malloc(sizeof(char *) * (numTokens+1));

    i=0;
    numTokens=0;

    while(tokens[i]){
        if(strcmp(tokens[i], "<")==0 || strcmp(tokens[i], ">")==0){
            i+=2;

        }else{

            newTokens[numTokens] = tokens[i];
            i++;
            numTokens++;
        }

    }
    free(tokens);
    newTokens[numTokens]='\0';

    return newTokens;
}

//adds spaces between carots and files, ex: <input.txt --> < input.txt
char **addSpaceCarots(char **tokens){
    int i=0;
    int numTokens=0;
    while(tokens[i]){
        if((tokens[i][0]== '<' && strlen(tokens[i])!=1) || (tokens[i][0]=='>' &&strlen(tokens[i])!=1)){
            i++;
            numTokens+=2;
        }else{
            i++;
            numTokens++;
        }
    }

    char **newTokens = (char **)malloc(sizeof(char *) * (numTokens+1));
    i=0;
    numTokens=0;

    while(tokens[i]){
        if(tokens[i][0]== '<' && strlen(tokens[i])!=1) {
            newTokens[numTokens]= "<";
            numTokens++;
            tokens[i]++;//removes first character
            newTokens[numTokens]= tokens[i];
            numTokens++;
        }else if(tokens[i][0]=='>' && strlen(tokens[i])!=1){
            newTokens[numTokens]= ">";
            numTokens++;
            tokens[i]++;//removes first character
            newTokens[numTokens]= tokens[i];
            numTokens++;
        }else{
            newTokens[numTokens]=tokens[i];
            numTokens++;
        }
        i++;
    }

    free(tokens);
    newTokens[numTokens]='\0';
    return newTokens;
}