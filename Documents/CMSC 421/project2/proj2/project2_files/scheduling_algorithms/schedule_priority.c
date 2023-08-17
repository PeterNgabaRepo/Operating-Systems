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
        printf("Prints the nodes data while traversing through the linked list and returning the last node to the scheduling system\n\n");

        printf("Initalizes temp and priority node to head\n\n");

        struct node* temp = head;
	struct node* priority = head;

	printf("Iterates through  linked list updating priority if the temp node's task is a higher priority than what we have saved\n\n");
        while (temp != NULL) {
                printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);

                if((temp->task)->priority >= priority->task->priority){
                        priority = temp;
                }

                temp = temp->next;
        }
	printf("Returns the node with the higherst priority\n\n");
        return priority;
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
        printf("Runs all the tasks in the linked list using the priority model and deletes task memory\n\n");
        printf("Thus runs the task with the higheest priority numbern\n");

        while(head != NULL){
                struct node* node = pickNextTask(head);
                run(node->task, (node->task)->burst);
                delete(&head, node->task);

        }
}




