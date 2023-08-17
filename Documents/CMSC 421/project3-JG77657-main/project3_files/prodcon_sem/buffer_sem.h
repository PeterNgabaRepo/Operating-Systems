#ifndef BUFFER_SEM_H
#define BUFFER_SEM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __KERNEL__
#include <semaphore.h>
#else
#include <linux/semaphore.h>
#endif

#define SIZE_OF_BUFFER 20
#define DATA_LENGTH 1024

typedef struct bb_node_421 {
    struct bb_node_421 *next;
    char data[DATA_LENGTH];
} bb_node_421_t;

typedef struct bb_buffer_421 {
    int length;
    bb_node_421_t *read;
    bb_node_421_t *write;
} bb_buffer_421_t;

#ifndef __KERNEL__
long init_buffer_421(void);
long enqueue_buffer_421(char *data);
long dequeue_buffer_421(char *data);
long delete_buffer_421(void);
void print_semaphores(void);
#endif

#ifdef __cplusplus
}
#endif

#endif