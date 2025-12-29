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
    size_t tail;
    size_t count;
} queue;

typedef struct {
    size_t pos;
    queue* cont;
} iterator;

void queue_create(queue* q);
bool queue_is_empty(const queue* q);
void queue_push_back(queue* q, const data_type elem);
void queue_push_front(queue* q, const data_type elem);
void queue_pop_front(queue* q);
void queue_pop_back(queue* q);
void queue_print(const queue* q);
void queue_print_recursive(const queue* q, size_t pos);
size_t queue_size(const queue* q);
void queue_insert(queue* q, const data_type elem);
void queue_erase(queue* q, key_type key);

data_type queue_at(const queue* q, size_t pos);
void queue_set(queue* q, size_t pos, const data_type elem);

iterator queue_begin(queue* q);
iterator iter_next(iterator it);
iterator iter_prev(iterator it);
data_type* iter_deref(iterator it);
bool iter_valid(iterator it);

#endif
