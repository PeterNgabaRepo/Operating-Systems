
#include <linux/kernel.h>
#include <linux/syscalls.h>
//#include <stdlib.h>
//#include <stdio.h>
#include "buffer.h"

static ring_buffer_421_t buffer;

SYSCALL_DEFINE0(init_buffer_421){

	if(buffer.read || buffer.write){
		printk("Buffer has already been initialized\n");
		return -1;
	}

	buffer.length = 0;

	struct node_421* curr;
	curr = (struct node_421*)kmalloc(sizeof(struct node_421), GFP_KERNEL);
	curr->data = 0;

	struct node_421* head;
	head = curr;

	int i;
	for(i = 0; i < SIZE_OF_BUFFER - 1; i++){

		curr->next = (struct node_421*)kmalloc(sizeof(struct node_421), GFP_KERNEL);

		curr->next->data = 0;

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

SYSCALL_DEFINE1(insert_buffer_421, int, i){

	if(!buffer.read && !buffer.write){
		printk("Buffer has not been initialized or has been deleted\n");
		return -1;
	}



	if(buffer.length == SIZE_OF_BUFFER){
		printk("Cannot insert, buffer is full!\n");
		return -1;
	}

	buffer.write->data = i;

	buffer.write = buffer.write->next;

	buffer.length++;

	return 0;

}


SYSCALL_DEFINE0(print_buffer_421){

	if(!buffer.read && !buffer.write){
		printk("Buffer has not been initialized\n");
		return -1;
	}

	int i;
	for(i = 0; i < buffer.length; i++){
//		struct node_421* curr = buffer.read;

		printk("NODE %d: %d\n", i, buffer.read->data);

		buffer.read = buffer.read->next;
//		curr = curr->next;
	}

	return 0;
}

SYSCALL_DEFINE0(delete_buffer_421){

	if(!buffer.read && !buffer.write){
		printk("Buffer has not been initialized\n");
		return -1;
        }

	struct node_421* curr = buffer.read;

	int i;
	for(i = 0; i < SIZE_OF_BUFFER; i++){
		struct node_421* head = curr;

		curr = curr->next;

		kfree(head);

	}

	buffer.read = NULL;
	buffer.write = NULL;

	buffer.length = 0;


	//print_buffer_421();

	return 0;
}




