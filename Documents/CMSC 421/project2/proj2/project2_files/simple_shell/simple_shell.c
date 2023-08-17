#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

const char* EXIT = "exit";
const char* SIMPLE = "simple";
const char* SHELL = "shell";
const int INIT_SIZE = 100;
int ARRAY_SIZE = INIT_SIZE;
const char* PROC = "proc";

void freeArrCont(char** arr, int i){
	int j;
	for(j = 0; j <= i; j++){
  	        free(arr[j]);
        }
}

int parseStrings(char* input, char** parsedArg){

        char* slice = input;

        char* result;

        int end = strlen(input);

        int spaceIndex = first_unquoted_space(slice);

        int i = 0;

        while(spaceIndex != -1){//make constant

		if(i == ARRAY_SIZE - 1){
			parsedArg = malloc( 2 * sizeof(parsedArg));
			ARRAY_SIZE = 2 * ARRAY_SIZE;
		}

                result = strndup(slice, spaceIndex);

                strncpy(slice, slice + spaceIndex + 1, end - spaceIndex);

                parsedArg[i] = result;

                spaceIndex = first_unquoted_space(slice);

                i++;
        }

        parsedArg[i] = slice;

	return i;
}

void simple_shell(char* input, char** parsedArg){

//	char* procDirec = malloc(INIT_SIZE * sizeof(char));
//	char procDirec [INIT_SIZE];

	int j;

	while(1){
		printf("$ ");

		size_t len = 0;

		getline(&input, &len, stdin);

	        int i = parseStrings(input, parsedArg);

		parsedArg[i] = NULL;

		if(strcmp(parsedArg[0], EXIT) == 0 && i <= 2){
                	free(input);

			freeArrCont(parsedArg, i);

			free(parsedArg);

                        if(i == 1){
                        	exit(0);
                        	}
                        else if(i == 2){
                        	int status = atoi(parsedArg[1]);
                         	exit(status);
                            	}
		}

		else if(strcmp(parsedArg[0], PROC) == 0){
//			printf("Read from file\n");

			char* procDirec = malloc(INIT_SIZE * sizeof(char));
//			procDirec = "/proc/";
			strcpy(procDirec,"/proc/");

			if(i > 1){
				for(j = 1; j < i; j++){
					strcat(procDirec, parsedArg[j]);
				}
//				printf("%s", procDirec);
			}

			FILE* fp;

			char* bufptr = 0;

			size_t buflen = 0;

//			char** outputArr = malloc( sizeof(char*) * INIT_SIZE) ;

			int i = 0;

			fp = fopen(procDirec, "r");

			while(getline(&bufptr, &buflen, fp) != -1){
				i++;
				printf("%s", bufptr);

			}


			fclose(fp);
			free(bufptr);
			free(procDirec);

		}

		else{

			pid_t retVal;
			retVal = fork();

			if(retVal < 0){
				printf("fork() failed\n");
			}
			else if(retVal == 0){
				execvp(parsedArg[0], parsedArg);
			}
			else{
				wait(NULL);
			}
		}

		free(input);
             	freeArrCont(parsedArg, i);
	}
}

void increaseArray(char** strings){
	strings = realloc(strings, 2 * sizeof(strings));
}

int main(){

	char** parsedArg = calloc(INIT_SIZE, sizeof(char*));
	char* input = malloc(sizeof(char*) * INIT_SIZE);
	size_t len = INIT_SIZE;

	printf("Enter shell command\n");

	getline(&input, &len, stdin);

	int i = parseStrings(input, parsedArg);

	if(strcmp(parsedArg[0],SIMPLE) == 0   && strcmp(parsedArg[1], SHELL) == 0 ){
		if(i == 2){
			freeArrCont(parsedArg, i);

			simple_shell(input, parsedArg);
		}
		else{
			fprintf(stderr, "Cannot initialize shell with cmd args\n");
		}

	}

	freeArrCont(parsedArg, i);

	free(parsedArg);

	return -1;
}
