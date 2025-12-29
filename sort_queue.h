#ifndef SORT_QUEUE_H
#define SORT_QUEUE_H

#include "queue.h"

void sort_queue_insertion_recursive(queue* q, size_t n);
void sort_queue(queue* q);
void queue_insert_sorted_recursive(queue* q, size_t i);

#endif
