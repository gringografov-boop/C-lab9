#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#include <stdio.h>

void queue_create(queue* q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool queue_is_empty(const queue* q) {
    return q->count == 0;
}

size_t queue_size(const queue* q) {
    return q->count;
}

void queue_push_back(queue* q, const data_type elem) {
    if (q->count >= 100) {
        fprintf(stderr, "Ошибка: очередь переполнена!\n");
        return;
    }

    size_t idx = (q->head + q->count) % 100;
    q->data[idx] = elem;
    q->count++;
}

void queue_push_front(queue* q, const data_type elem) {
    if (q->count >= 100) {
        fprintf(stderr, "Ошибка: очередь переполнена!\n");
        return;
    }

    q->head = (q->head + 99) % 100;
    q->data[q->head] = elem;
    q->count++;
}

void queue_pop_front(queue* q) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Ошибка: очередь пуста!\n");
        return;
    }

    q->head = (q->head + 1) % 100;
    q->count--;
}

void queue_pop_back(queue* q) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Ошибка: очередь пуста!\n");
        return;
    }

    q->count--;
}

data_type queue_front(const queue* q) {
    return q->data[q->head];
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

void queue_print_recursive(const queue* q, size_t pos) {
    queue_print_recursive_impl(q, pos);
}

void queue_print(const queue* q) {
    if (queue_is_empty(q)) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь (%lu элементов): ", (unsigned long)q->count);
    queue_print_recursive_impl(q, 0);
}

void queue_insert(queue* q, const data_type elem) {
    if (q->count >= 100) {
        fprintf(stderr, "Ошибка: очередь переполнена!\n");
        return;
    }

    size_t pos = 0;
    while (pos < q->count) {
        size_t idx = (q->head + pos) % 100;
        data_type cur = q->data[idx];
        if (cur.key >= elem.key) {
            break;
        }
        pos++;
    }

    size_t i = q->count;
    while (i > pos) {
        size_t from = (q->head + i - 1) % 100;
        size_t to   = (q->head + i) % 100;
        q->data[to] = q->data[from];
        i--;
    }

    size_t insert_idx = (q->head + pos) % 100;
    q->data[insert_idx] = elem;
    q->count++;
}

void queue_erase(queue* q, key_type key) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Ошибка: очередь пуста!\n");
        return;
    }

    size_t pos = 0;
    while (pos < q->count) {
        size_t idx = (q->head + pos) % 100;
        data_type cur = q->data[idx];

        if (cur.key == key) {
            size_t i = pos;
            while (i + 1 < q->count) {
                size_t from = (q->head + i + 1) % 100;
                size_t to   = (q->head + i) % 100;
                q->data[to] = q->data[from];
                i++;
            }
            q->count--;
            return;
        }

        pos++;
    }

    fprintf(stderr, "Ошибка: элемент с ключом %d не найден!\n", key);
}
