#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node* head = NULL;

struct node* pickNextTask(struct node* head, struct node* prevRet, int delete2){
	printf("\n");
	printf("Traverses the Linked List printing the tasks\n\n");

	traverse(head);
	struct node* priority_rr;

	printf("Updates priority_rr to correct value based on corresponding factors\n\n");

	if(prevRet != NULL && prevRet->next != NULL){
		priority_rr = prevRet->next;
	}
	if( prevRet == NULL || prevRet->next == NULL) {
		priority_rr = head;
	}

	if(delete2 == 1 && prevRet != NULL ){
		priority_rr = prevRet;
	}
	printf("Returns the selected linked list node\n\n");
	return priority_rr;
}

void sortList(struct node* head){
	struct node* temp = head;
	struct node* priority_rr = NULL;

	printf("Sorts linked list into priority descending order\n\n");
        while (temp != NULL) {

		priority_rr = temp->next;

		while(priority_rr != NULL){
			if(temp->task->priority < priority_rr->task->priority){
				printf("Swaps task in nodes if it has a lower priority\n\n");
				struct task* swap = temp->task;
				temp->task = priority_rr->task;
				priority_rr->task = swap;

			}
			priority_rr = priority_rr->next;
		}
		temp = temp->next;
	}

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
        printf("Runs all the tasks in the linked list using the priority_rr model and deletes task memory\n\n");

        struct node* node = NULL;

	sortList(head);
	int delete2 = 0;

        while(head != NULL){
                node = pickNextTask(head, node, delete2);
		delete2 = 0;
		printf("Gets next node to run\n\n");

                if((node->task)->burst < QUANTUM){
                        run(node->task, (node->task)->burst);
                        (node->task)->burst = 0;
                }
                else{
                        run(node->task, QUANTUM);
                        (node->task)->burst = (node->task)->burst - QUANTUM;
                }

                if((node->task)->burst == 0){
			struct node* node2 = node->next;

			printf("After executing node, it saves the node's next and deletes the temp node\n\n");

                        delete(&head, node->task);
			node = node2;
			delete2 = 1;
                }
        }
}




