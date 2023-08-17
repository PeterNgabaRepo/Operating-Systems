#include <linux/kernel.h>
#include <linux/syscalls.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <semaphore.h>
#include "buffer_sem.h"
#include <linux/semaphore.h>

static bb_buffer_421_t buffer;
static struct semaphore  mutex;
static struct semaphore fill_count;
static struct semaphore empty_count;
static int waiting = 1;

SYSCALL_DEFINE0(init_buffer_sem_421) {
	// Write your code to initialize buffer

	// Initialize your semaphores here.
	sema_init(&mutex, 1);
	sema_init(&fill_count, 0);
	sema_init(&empty_count, SIZE_OF_BUFFER);

	if(buffer.read || buffer.write){
		printk("Buffer has already been initialized\n");
		return -1;
	}

	buffer.length = 0;

	struct bb_node_421* curr = (struct bb_node_421*)kmalloc(sizeof(struct bb_node_421), GFP_KERNEL);
	int i;
	for(i = 0; i < DATA_LENGTH; i++){
		curr->data[i] = '0';
	}

	struct bb_node_421* head = curr;

	for(i = 0; i < SIZE_OF_BUFFER - 1; i++){

		curr->next = (struct bb_node_421*)kmalloc(sizeof(struct bb_node_421), GFP_KERNEL);

		for(i = 0; i < DATA_LENGTH; i++){
			curr->next->data[i] = '0';
		}

		curr = curr->next;
	}

	curr->next = head;

	buffer.read = head;
	buffer.write = head;

	if(buffer.read != head && buffer.write != head){
		printk("Error upon initialization\n");
		return -1;
	}

	return 0;
}


SYSCALL_DEFINE1(enqueue_buffer_sem_421, char*, data) {
	// Write your code to enqueue data into the buffer
//	buffer.length = 0;
	if(!buffer.read && !buffer.write){
		printk("Buffer has not been initialized\n");
		return -1;
	}

	waiting = 0;
	down(&empty_count);
	down(&mutex);


	waiting = 1;

	buffer.length++;
	memcpy(buffer.write->data, data, 1024);
	buffer.write = buffer.write->next;

//	print_semaphores();

	printk("ENQUEUING: ");
	int i;
/*	for(i = 0; i < DATA_LENGTH; i++){
		printk("%c", data[i]);
	}
*/

	printk("%c", data[0]);

	printk("\n");

	up(&fill_count);

//	print_semaphores();
	up(&mutex);
	return 0;
}

SYSCALL_DEFINE1(dequeue_buffer_sem_421, char*, data) {

	// Write your code to dequeue data from the buffer

	if(!buffer.read && !buffer.write){
		printk("Buffer has not been initialized\n");
		return -1;
	}

	waiting = 0;
	down(&fill_count);
	down(&mutex);
//	sem_wait(&fill_count);

	waiting = 1;

	printk("\n");
	printk("DEQUEUING: ");

	memcpy(data, buffer.read->data, 1024);
	buffer.read = buffer.read->next;
	buffer.length--;

	int i;

/*
	for(i = 0; i < DATA_LENGTH; i++){
		printk("%c", data[i]);
	}
*/
	printk("%c", data[0]);

	printk("\n");

//	print_semaphores();

	up(&empty_count);
//	print_semaphores();
	up(&mutex);
	return 0;
}


SYSCALL_DEFINE0(delete_buffer_sem_421) {
	// Tip: Don't call this while any process is waiting to enqueue or dequeue.
	// write your code to delete buffer and other unwanted components


	if(waiting == 0){
		printk("Cannot delete buffer because there is a thread waiting to be executed");
		return -1;
	}

	if(!buffer.read && !buffer.write){
		printk("Buffer has not been initialized\n");
		return -1;
	}


	down(&mutex);

	struct bb_node_421* curr = buffer.read;
	int i;
	for(i = 0; i < SIZE_OF_BUFFER; i++){
		struct bb_node_421* head = curr;

		curr = curr->next;

		kfree(head);

	}

	buffer.length = 0;
	buffer.read = NULL;
	buffer.write = NULL;

//	sem_destroy(&mutex);
//	sem_destroy(&fill_count);
//	sem_destroy(&empty_count);

	return 0;
}

/*
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
*/
