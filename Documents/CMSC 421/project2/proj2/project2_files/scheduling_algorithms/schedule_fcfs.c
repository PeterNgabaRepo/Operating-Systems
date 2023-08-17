#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node* head = NULL;

struct node* pickNextTask(struct node* head){
	printf("Prints the nodes data while traversing through the linked list and returning the last node to the scheduling system\n\n");

	printf("Initalizes temp node to head\n\n");
	struct node* temp = head;

    	while (temp != NULL) {
		printf("Prints temp node and returns it if its next node is null\n\n");
        	printf("[%s] [%d] [%d]\n\n",temp->task->name, temp->task->priority, temp->task->burst);
		if((temp->next) == NULL){
			printf("Return temp node to run\n\n");
			return temp;
		}
		printf("Sets the current node to its next to iterate\n\n");
        	temp = temp->next;
    	}
	return temp;
}


void add(char *name, int priority, int burst){
	printf("This function allocattes memory for the the task, initalizes the data and inserts it into the Linked List\n\n");

	struct task* t = malloc(sizeof(struct task));

	t->name = name;
	t->priority = priority;
	t->burst = burst;

	insert(&head, t);

}

void schedule(){

	printf("Runs all the tasks in the linked list using the fcfs model and deletes task memory\n\n");
	printf("Thus running the last node")

	while(head != NULL){
		struct node* node = pickNextTask(head);
		run(node->task, (node->task)->burst);
		delete(&head, node->task);
	}
}
