#ifndef BUFFER_H
#define BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#define SIZE_OF_BUFFER 20

typedef struct node_421 {
	struct node_421 *next;
	int data;
} node_421_t;

typedef struct ring_buffer_421 {
   int length;
   node_421_t *read;
   node_421_t *write;
} ring_buffer_421_t;

#ifndef __KERNEL__
long init_buffer_421(void);
long insert_buffer_421(int i);
long print_buffer_421(void);
long delete_buffer_421(void);
#endif

#ifdef __cplusplus
}
#endif
#endif
