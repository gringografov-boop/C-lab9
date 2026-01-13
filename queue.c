#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#include <stdio.h>

void queue_create(queue* q) {
    q->head  = 0;
    q->count = 0;
}

void queue_destroy(queue* q) {
    (void)q;
}

bool queue_is_empty(const queue* q) {
    return q->count == 0;
}

size_t queue_size(const queue* q) {
    return q->count;
}

bool queue_push(queue* q, const data_type elem) {
    if (q->count >= 100) {
        fprintf(stderr, "Ошибка: очередь переполнена!\n");
        return false;
    }

    size_t idx = (q->head + q->count) % 100;
    q->data[idx] = elem;
    q->count++;
    return true;
}

bool queue_pop(queue* q, data_type* out) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Ошибка: очередь пуста!\n");
        return false;
    }

    if (out) {
        *out = q->data[q->head];
    }
    q->head = (q->head + 1) % 100;
    q->count--;
    return true;
}

bool queue_front(const queue* q, data_type* out) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Ошибка: очередь пуста!\n");
        return false;
    }
    if (out) {
        *out = q->data[q->head];
    }
    return true;
}

static void queue_print_recursive_impl(const queue* q, size_t pos) {
    if (pos >= q->count) {
        printf("\n");
        return;
    }

    size_t idx = (q->head + pos) % 100;
    data_type elem = q->data[idx];
    printf("[key=%d, val=%d] ", elem.key, elem.value);

    queue_print_recursive_impl(q, pos + 1);
}

void queue_print(const queue* q) {
    if (queue_is_empty(q)) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь (%zu элементов): ", queue_size(q));
    queue_print_recursive_impl(q, 0);
}

iterator queue_begin(queue* q) {
    iterator it;
    it.cont = q;
    it.pos  = 0;
    return it;
}

bool iter_valid(iterator it) {
    if (it.cont == NULL) return false;
    return it.pos < queue_size(it.cont);
}

iterator iter_next(iterator it) {
    if (!iter_valid(it)) {
        return it;
    }
    it.pos++;
    return it;
}

iterator iter_prev(iterator it) {
    if (it.cont == NULL) return it;
    if (it.pos == 0) return it;
    it.pos--;
    return it;
}

data_type* iter_deref(iterator it) {
    if (!iter_valid(it)) {
        return NULL;
    }
    queue* q = it.cont;
    size_t idx = (q->head + it.pos) % 100;
    return &q->data[idx];
}

