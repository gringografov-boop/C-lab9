#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int key_type;
typedef int value_type;

typedef struct {
    key_type key;
    value_type value;
} data_type;

typedef struct {
    data_type data[100];
    size_t head;
    size_t count;
} queue;

void   queue_create(queue* q);
void   queue_destroy(queue* q);

bool   queue_is_empty(const queue* q);
size_t queue_size(const queue* q);

bool   queue_push(queue* q, const data_type elem);
bool   queue_pop(queue* q, data_type* out);
bool   queue_front(const queue* q, data_type* out);

void   queue_print(const queue* q);

#endif
