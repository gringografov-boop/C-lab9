#define _CRT_SECURE_NO_WARNINGS
#include "sort_queue.h"
#include <stdio.h>

static void insert_sorted(queue* q, data_type elem, size_t n) {
    if (n == 0) {
        queue_push(q, elem);
        return;
    }

    data_type front_elem;
    queue_front(q, &front_elem);
    queue_pop(q, NULL);

    if (elem.key <= front_elem.key) {
        queue_push(q, elem);
        queue_push(q, front_elem);
    } else {
        queue_push(q, front_elem);
        insert_sorted(q, elem, n - 1);
    }
}

static void sort_queue_recursive(queue* q) {
    if (queue_is_empty(q)) {
        return;
    }

    data_type x;
    queue_pop(q, &x);
    sort_queue_recursive(q);
    insert_sorted(q, x, queue_size(q));
}

void sort_queue(queue* q) {
    printf("\nНачало сортировки очереди (вставками, рекурсивно)\n");
    if (queue_size(q) <= 1) {
        printf("Очередь уже отсортирована (0 или 1 элемент)\n");
        return;
    }

    sort_queue_recursive(q);
    printf("--- Конец сортировки ---\n");
}
