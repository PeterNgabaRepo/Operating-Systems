
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;
static int waiting = 1;

long init_buffer_421(void) {
	// Write your code to initialize buffer

	// Initialize your semaphores here.
	sem_init(&mutex, 0, 1);
	sem_init(&fill_count, 0, 0);
	sem_init(&empty_count, 0, SIZE_OF_BUFFER);

	if(buffer.read || buffer.write){
		printf("Buffer has already been initialized\n");
		return -1;
	}

	buffer.length = 0;

	struct bb_node_421* curr = (struct bb_node_421*)malloc(sizeof(struct bb_node_421));
	for(int i = 0; i < DATA_LENGTH; i++){
		curr->data[i] = '0';
	}

	struct bb_node_421* head = curr;

	for(int i = 0; i < SIZE_OF_BUFFER - 1; i++){

		curr->next = (struct bb_node_421*)malloc(sizeof(struct bb_node_421));

		for(int i = 0; i < DATA_LENGTH; i++){
			curr->next->data[i] = '0';
		}

		curr = curr->next;
	}

	curr->next = head;

	buffer.read = head;
	buffer.write = head;

	if(buffer.read != head && buffer.write != head){
		printf("Error upon initialization\n");
		return -1;
	}

	return 0;
}


long enqueue_buffer_421(char * data) {
	// Write your code to enqueue data into the buffer
//	buffer.length = 0;
	if(!buffer.read && !buffer.write){
		printf("Buffer has not been initialized\n");
		return -1;
	}

	waiting = 0;
	sem_wait(&empty_count);
	sem_wait(&mutex);


	waiting = 1;

	buffer.length++;
	memcpy(buffer.write->data, data, 1024);
	buffer.write = buffer.write->next;

//	print_semaphores();

	printf("ENQUEUING: ");

	for(int i = 0; i < DATA_LENGTH; i++){
		printf("%c", data[i]);
	}

	printf("\n");

	sem_post(&fill_count);

	print_semaphores();
	sem_post(&mutex);
	return 0;
}

long dequeue_buffer_421(char * data) {

	// Write your code to dequeue data from the buffer

	if(!buffer.read && !buffer.write){
		printf("Buffer has not been initialized\n");
		return -1;
	}

	waiting = 0;
	sem_wait(&fill_count);
	sem_wait(&mutex);
//	sem_wait(&fill_count);

	waiting = 1;

	printf("\n");
	printf("DEQUEUING: ");

	memcpy(data, buffer.read->data, 1024);
	buffer.read = buffer.read->next;
	buffer.length--;


	for(int i = 0; i < DATA_LENGTH; i++){
		printf("%c", data[i]);
	}

	printf("\n");

//	print_semaphores();

	sem_post(&empty_count);
	print_semaphores();
	sem_post(&mutex);
	return 0;
}


long delete_buffer_421(void) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// write your code to delete buffer and other unwanted components


	if(waiting == 0){
		printf("Cannot delete buffer because there is a thread waiting to be executed");
		return -1;
	}

	if(!buffer.read && !buffer.write){
		printf("Buffer has not been initialized\n");
		return -1;
	}


	sem_wait(&mutex);

	struct bb_node_421* curr = buffer.read;

	for(int i = 0; i < SIZE_OF_BUFFER; i++){
		struct bb_node_421* head = curr;

		curr = curr->next;

		free(head);

	}

	buffer.length = 0;
	buffer.read = NULL;
	buffer.write = NULL;

	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);

	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
