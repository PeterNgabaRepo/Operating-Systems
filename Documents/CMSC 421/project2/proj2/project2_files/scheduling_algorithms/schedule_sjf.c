#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node* head = NULL;

struct node* pickNextTask(struct node* head){
	printf("\n");
        printf("Prints the nodes data while traversing through the scheduling system\n\n");

	printf("Initalizes temp and sjf nodes  to head\n\n");
        struct node* temp = head;
	struct node* sjf = head;

        while (temp != NULL) {
		printf("Prints temp node and sets sjf to temp if temp burst is less than sjf burst\n\n");

                printf("[%s] [%d] [%d]\n\n",temp->task->name, temp->task->priority, temp->task->burst);
                if((temp->task)->burst < (sjf->task)->burst){
                        sjf = temp;
                }

		printf("Sets the current node to its next node\n\n");
                temp = temp->next;
        }
        return sjf;
}


void add(char *name, int priority, int burst){
        struct task* t = malloc(sizeof(struct task));
        printf("This function allocattes memory for the the task, initalizes the data and inserts it into the Linked List\n\n");

        t->name = name;
        t->priority = priority;
        t->burst = burst;

        insert(&head, t);

}

void schedule(){
        printf("Runs all the tasks in the linked list using the sjf model and deletes task memory.\n\n");
        printf("Thus running the job with the smallest burst time first\n\n");


        while(head != NULL){
                struct node* node = pickNextTask(head);
                run(node->task, (node->task)->burst);
                delete(&head, node->task);
        }
}



