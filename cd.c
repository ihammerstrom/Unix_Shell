#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "cd.h"
#include "pwd.h"

//uses the function "chdir" to change directory
int cd (char *newDirectory){
	if(newDirectory){
		int ret = chdir(newDirectory);
		if(ret==0){
			printf("cwd changed to ");
			pwd();
		}else{
			printf("No such directory: %s", newDirectory);
		}

	    return ret;

	}else{
		return 1;
	}
}