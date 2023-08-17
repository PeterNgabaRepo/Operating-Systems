#ifndef BUFFER_MON_H
#define BUFFER_MON_H

#ifdef __cplusplus
extern "C" {
#endif

#define SIZE_OF_BUFFER 20
#define DATA_LENGTH 1024

typedef struct node_421 {
    struct node_421 *next;
    char data[DATA_LENGTH];
} node_421_t;

typedef struct ring_buffer_421 {
    int length;
    node_421_t *read;
    node_421_t *write;
} ring_buffer_421_t;

long init_buffer_421(void);
long enqueue_buffer_421(char *data);
long dequeue_buffer_421(char *data);
long delete_buffer_421(void);

#ifdef __cplusplus
}
#endif

#endif
