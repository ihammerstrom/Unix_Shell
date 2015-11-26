#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

/*
 Ian Hammerstrom
 July 12th, 2015
 CSCI 352 Warmup 2 - Tokenizer

 Takes a string line as a parameter and returns a NULL-terminated array of substrings from line. 
 */

int getLengthToken(char *line, int i, int *pJump, char **tokens, int j);

char **gettokens(char *line) {
    int i = 0, j = 0, numTokens=0, length=0;
    int jump=0, tempJump;
    int *pJump = &jump;//pointer for accounting for quote when calculating token length
    char **tokens;
#if DEBUG
    printf("line is: %s\n", line);
#endif
    while(line[i]){ //getting number of tokens for memory allocation
#if DEBUG
        printf("Line[%d] is: %c\n", i, line[i]);
#endif
        i += getLengthToken(line, i, pJump, NULL, 0);
#if DEBUG
        printf("i is %d and line[%d] is %c", i, i, line[i]);
#endif

        i += *pJump;//incrementing i by the length and possible a quote jump value of 1
        *pJump=0;
        numTokens++;
        i++;
    }
#if DEBUG
    printf("\nnumTokens is %d\n\n", numTokens);
#endif
    // allocating for number of tokens with space for null character at end;
    tokens = (char **) malloc(((numTokens+1) * sizeof(char *)));    

    i=0;

    while(line[i]){ //getting length of tokens for memory allocation
        length = getLengthToken(line, i, pJump, NULL, 0);
        i+= length + *pJump;//incrementing i by the length and possible a quote jump value of 1
        *pJump=0;
        tokens[j] = (char *) malloc( length * sizeof(char) +1 );
        j++;
        i++;
    }
#if DEBUG
    printf("\ndone1\n\n");
#endif

    i=0;
    j=0;

    while(line[i]){ // filling tokens[][] with characters from line
        tempJump = *pJump;
        length = getLengthToken(line, i, pJump, NULL, 0);//get the length
        *pJump= tempJump;
        getLengthToken(line, i, pJump, tokens, j);//add to tokens at j

        i+= length + *pJump;//incrementing i by the length and possible a quote jump value of 1
        *pJump=0;

        j++;
        i++;

    }
#if DEBUG
    printf("\ndone2, j ends on %d\n\n", j-1);
#endif

    tokens[j] = (char *) malloc(sizeof(char));
    tokens[j] = '\0'; //adding terminating null character at end

    return tokens;
}

/*getLengthToken returns the length of the token starting at index i, and if tokens is passed in as a
parameter, adds the characters to tokens at index j and the current counted length.
*/

int getLengthToken(char *line, int i, int *pJump, char **tokens, int j){
    int numQuotes=0, endSpace=1, length=0; //numQuotes and endSpace treated as boolean

    while(line[i] && line[i]==' ')i++;//get past any beginning whitespaces

    for(; line[i]; i++){
#if DEBUG
        if(i<10){
            putchar(' ');//formatting
        }
        printf("line[%d]=%c, numQuotes=%d, endSpace=%d, length=%d\n", i, line[i], numQuotes, endSpace, length);
#endif

        if(line[i]=='"' && numQuotes==1){
            (*pJump)++; //increments i by one in return to account for space of quote;
            endSpace=1;
        }else if(line[i]=='"' && numQuotes==0){//openning quote
            numQuotes=1;
            endSpace=0;
        }else if(line[i]==' ' && endSpace ==1){//ending space
#if DEBUG
            printf("getLength returned %d (ending space)\n", length);
#endif

            return length;
        }else{
            if(tokens){//if tokens has been passed as non-null
#if DEBUG
                printf("\nattempting tokens[%d][%d]=line[%d]=%c\n", j,length,i,line[i] );
#endif

                tokens[j][length]=line[i];//assigning tokens at j and length to i
            }
            length++;
        }
    }
#if DEBUG
    if(i<10){
        putchar(' ');//formatting
    }
    printf("line[%d]=%c, numQuotes=%d, endSpace=%d, length=%d\n", i, line[i], numQuotes, endSpace, length);
    printf("getLength returned %d (end of line)\n", length);
#endif

    return length;
}










