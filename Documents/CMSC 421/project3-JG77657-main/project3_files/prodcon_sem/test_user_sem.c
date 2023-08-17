#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "buffer_sem.h"
#include <unistd.h>

const int PASSED = 0;
const int FAILED = -1;

int test_init_buffer(){
        int val = init_buffer_421();
        printf("Result of init fxn: %d \n", val);

        return val;
}

int test_enqueue_buffer(char* arr){
        int val = enqueue_buffer_421(arr);
        printf("Result of insert fxn: %d \n", val);

        return val;
}


int test_dequeue_buffer(char* arr){
        int val = dequeue_buffer_421(arr);
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


void* producer(void* how){
	int ascii = 48;

	char j;
	char arr[1024] = {0};

	for(int i = 0; i < 1000; i++){
		//int r = rand() % 2;
		double r = ((double) rand() / (RAND_MAX));
		sleep(r);

		if(ascii >= ':'){
			ascii = 48;
		}

		j = ascii;

/*		if( j > '9'){
			j = ((ascii % ':') % 10) + '0';
		}
*/
//		printf("THIS IS J: %c\n", j);

		for(int l = 0; l < DATA_LENGTH; l++){
			arr[l] = j;
		}

		printResults(test_enqueue_buffer(arr), PASSED);

		ascii++;
	}
	return NULL;
}

void* consumer(void* how){
	char arr[1024] = {'0'};

	for(int i = 0; i < 1000; i++){
//		int r = rand() % 2;

		double r = ((double) rand() / (RAND_MAX));

		sleep(r);

		printResults(test_dequeue_buffer(arr), PASSED);

	}

	return NULL;
}

int main(){
	pthread_t t1, t2;

//	printResults(test_init_buffer(), PASSED);
/*
	int ascii = 48;
	char j;
	char arr[1024] = {0};

//        int result;

	//delete edge case
	printResults(test_delete_buffer(), FAILED);

	//enqueue edge case
	printResults(test_enqueue_buffer(arr), FAILED);

	//dequeue edge case
	printResults(test_dequeue_buffer(arr), FAILED);

	//init test
	printResults(test_init_buffer(), PASSED);

//	Insert Test to Ensure Array has Correct Values and Are populated Correctly and Semaphore Works
	for(int i = 0; i < 20; i++){

		j = ascii;
		if( j > '9'){
			j = ((ascii % ':') % 10) + '0';
		}
		printf("THIS IS J: %c\n", j);


		for(int l = 0; l < DATA_LENGTH; l++){
			arr[l] = j;
		}

		for(int k = 0; k < DATA_LENGTH; k++){
			printf("%c", arr[k]);
		}
		printf("\n");

		printResults(test_enqueue_buffer(arr), PASSED);

		print_semaphores();

		ascii++;
	}


	//print buffer's data
	for(int i = 0; i < 20; i++){
		printResults(test_dequeue_buffer(arr), PASSED);

		for(int j = 0; j < DATA_LENGTH; j++){
			printf("%c", arr[j]);
		}
		printf("\n");
		print_semaphores();
		printf("\n\n");
	}

	printResults(test_delete_buffer(), PASSED);

	printResults(test_enqueue_buffer(arr), FAILED);
*/
	//Reinitalizing deleted buffer
	printResults(test_init_buffer(), PASSED);


	pthread_create(&t1, NULL, producer, NULL);

	pthread_create(&t2, NULL, consumer, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printResults(test_delete_buffer(), PASSED);

        return 0;
}
