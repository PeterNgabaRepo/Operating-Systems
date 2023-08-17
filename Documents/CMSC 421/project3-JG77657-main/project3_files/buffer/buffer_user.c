#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

static ring_buffer_421_t buffer;

long init_buffer_421(void){

	if(buffer.read || buffer.write){
		printf("Buffer has already been initialized\n");
		return -1;
	}

	buffer.length = 0;

	node_421* curr = (node_421*)malloc(sizeof(node_421));
	curr->data = 0;

	node_421* head = curr;

	for(int i = 0; i < SIZE_OF_BUFFER - 1; i++){

		curr->next = (node_421*)malloc(sizeof(node_421));

		curr->next->data = 0;

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

long insert_buffer_421(int i){

	if(!buffer.read && !buffer.write){
		printf("Buffer has not been initialized or has been deleted\n");
		return -1;
	}



	if(buffer.length == SIZE_OF_BUFFER){
		printf("Cannot insert, buffer is full!\n");
		return -1;
	}

	buffer.write->data = i;

	buffer.write = buffer.write->next;

	buffer.length++;

	return 0;

}


long print_buffer_421(){

	if(!buffer.read && !buffer.write){
		printf("Buffer has not been initialized\n");
		return -1;
	}


	for(int i = 0; i < SIZE_OF_BUFFER; i++){
//		node_421* curr = buffer.read;

		printf("NODE %d: %d\n", i, buffer.read->data);

//		curr = curr->next;
		buffer.read = buffer.read->next;
	}

	return 0;
}

long delete_buffer_421(){

	if(!buffer.read && !buffer.write){
		printf("Buffer has not been initialized\n");
		return -1;
        }

	node_421* curr = buffer.read;

	for(int i = 0; i < SIZE_OF_BUFFER; i++){
		node_421* head = curr;

		curr = curr->next;

		free(head);

	}

	buffer.read = NULL;
	buffer.write = NULL;

	buffer.length = 0;


	//print_buffer_421();

	return 0;
}




