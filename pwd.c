#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "pwd.h"


//prints the path using the function "getcwd"
char *pwd (void){
    char *cwd;
    char buffer[PATH_MAX];
    cwd = getcwd(buffer, PATH_MAX);
    if(cwd!=NULL){
        printf("%s",cwd);
    }
    return cwd;

}