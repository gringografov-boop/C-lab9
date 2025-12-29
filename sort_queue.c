#define _CRT_SECURE_NO_WARNINGS
#include "sort_queue.h"
#include <stdio.h>

static void insert_recursive(queue* q, size_t text, data_type elem, size_t n) {
    if (text == 0) {
        queue_set(q, 0, elem);
        return;
    }

    data_type prev = queue_at(q, text - 1);

    if (prev.key <= elem.key) {
        queue_set(q, text, elem);
        return;
    }

    queue_set(q, text, prev);
    insert_recursive(q, text - 1, elem, n);
}

void sort_queue_insertion_recursive(queue* q, size_t n) {
    if (n >= q->count) {
        return;
    }

    data_type current = queue_at(q, n);

    insert_recursive(q, n, current, n);

    sort_queue_insertion_recursive(q, n + 1);
}

void sort_queue(queue* q) {
    printf("\n--- Начало сортировки вставками (рекурсивно) ---\n");
    if (q->count <= 1) {
        printf("Очередь уже отсортирована (0 или 1 элемент)\n");
        return;
    }

    sort_queue_insertion_recursive(q, 1);
    printf("--- Конец сортировки ---\n");
}

void queue_insert_sorted_recursive(queue* q, size_t i) {
    if (i == 0) {
        return;
    }

    data_type curr = queue_at(q, i);
    data_type prev = queue_at(q, i - 1);

    if (curr.key < prev.key) {
        queue_set(q, i, prev);
        queue_set(q, i - 1, curr);
        queue_insert_sorted_recursive(q, i - 1);
    }
}
