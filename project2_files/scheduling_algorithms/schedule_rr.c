#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node* head = NULL;

struct node* pickNextTask(struct node* head, struct node* prevRet){
        printf("Prints the nodes data while traversing through the linked list and returning the last node to the scheduling system\n\n");

        printf("Initalizes temp node to head\n\n");

        struct node* temp = head;
	struct node* rr = head;
	int i = 1;

        while (temp != NULL) {

		printf("Prints temp node and returns it if its next node is null\n\n");
                printf("[%s] [%d] [%d]\n\n",temp->task->name, temp->task->priority, temp->task->burst);

		printf("Sets round robin node to temp if the temp's next node is the previously run task\n\n");
		if((temp->next) == prevRet && prevRet != head){
                        rr = temp;
			i = 0;
                }

		else if (i == 1){
			rr = temp;
		}
		printf("if (prevRet == head or the if statment above was not triggered temp is last node");

		printf("Sets the current node to its next to iterate\n\n");
                temp = temp->next;
        }
        return rr;
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

	struct node* node = NULL;

	printf("Runs the selected task and decrements QUANTUM from the task's burst until it is 0. IF the burst is 0 it deletes from the linked list and frees up memory");
        while(head != NULL){
               	node = pickNextTask(head, node);

		if((node->task)->burst < QUANTUM){
			run(node->task, (node->task)->burst);
			(node->task)->burst = 0;
		}
		else{
                	run(node->task, QUANTUM);
			(node->task)->burst = (node->task)->burst - QUANTUM;
		}

		if((node->task)->burst == 0){
                	delete(&head, node->task);
		}
        }
}



