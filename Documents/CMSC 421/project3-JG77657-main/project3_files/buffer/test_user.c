
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"


const int PASSED = 0;
const int FAILED = -1;


int test_init_buffer(){
	int val = init_buffer_421();
	printf("Result of init fxn: %d \n", val);

	return val;
}

int test_insert_buffer(int i){
        int val = insert_buffer_421(i);
        printf("Result of insert fxn: %d \n", val);

        return val;
}

int test_print_buffer(){
        int val = print_buffer_421();
        printf("Result of print fxn: %d \n", val);

        return val;
}

int test_delete_buffer(){
	int val = delete_buffer_421();
	printf("Result of delete fxn: %d \n", val);

	return val;
}


void printResults(int result, int expected){
	if(result == expected){
		printf("Test has passed\n\n");
	}
	else{
		printf("Test has failed\n\n");
	}

}

int main(){
	//delete edge case
	int result = test_delete_buffer();

	printResults(result, FAILED);

	//insert edge case
	result = test_insert_buffer(0);
	printResults(result, FAILED);

	//print edge case
	result = test_print_buffer();
	printResults(result, FAILED);

	//init test
	result = test_init_buffer();

	printResults(result, PASSED);

	//insert test until it is full and keep inserting
	for(int i = 0; i < 25; i++){
		result = test_insert_buffer(i);

		if(i < 20){
			printResults(result, PASSED);
		}
		else{
			printResults(result, FAILED);
		}
	}

	//init edge case
	result = test_init_buffer();

	printResults(result, FAILED);

	//print nodes
	result = test_print_buffer();

	printResults(result, PASSED);


	//delete buffer
	result = test_delete_buffer();

	printResults(result, PASSED);

	//insert into deleted buffer
	result = test_insert_buffer(0);

        printResults(result, FAILED);

	return 0;
}
