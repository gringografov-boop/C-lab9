#define _CRT_SECURE_NO_WARNINGS
#include "sort_queue.h"
#include <stdio.h>

static void queue_insert_sorted(queue* q, data_type elem) {
    queue buf;
    queue_create(&buf);

    int inserted = 0;
    size_t n = queue_size(q);

    for (size_t i = 0; i < n; ++i) {
        data_type cur = queue_front(q);
        queue_pop_front(q);

        if (!inserted && elem.key < cur.key) {
            queue_push_back(&buf, elem);
            inserted = 1;
        }
        queue_push_back(&buf, cur);
    }

    if (!inserted) {
        queue_push_back(&buf, elem);
    }

    n = queue_size(&buf);
    for (size_t i = 0; i < n; ++i) {
        data_type cur = queue_front(&buf);
        queue_pop_front(&buf);
        queue_push_back(q, cur);
    }
}

static void sort_queue_recursive(queue* q, size_t processed) {
    size_t n = queue_size(q);
    if (processed >= n) {
        return;
    }

    data_type x = queue_front(q);
    queue_pop_front(q);

    sort_queue_recursive(q, processed + 1);
    queue_insert_sorted(q, x);
}

void sort_queue_insertion_recursive(queue* q, size_t n) {
    (void)n;
    sort_queue_recursive(q, 0);
}

void sort_queue(queue* q) {
    printf("\nНачало сортировки очереди (вставками, рекурсивно)\n");
    if (queue_size(q) <= 1) {
        printf("Очередь уже отсортирована (0 или 1 элемент)\n");
        return;
    }

    sort_queue_insertion_recursive(q, 0);
    printf("--- Конец сортировки ---\n");
}

void queue_insert_sorted_recursive(queue* q, size_t i) {
    (void)q;
    (void)i;
}
