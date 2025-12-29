#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#include <stdio.h>
#include <string.h>

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

data_type queue_at(const queue* q, size_t pos) {
    data_type result;
    result = q->data[(q->head + pos) % 100];
    return result;
}

void queue_set(queue* q, size_t pos, const data_type elem) {
    q->data[(q->head + pos) % 100] = elem;
}

void queue_print_recursive(const queue* q, size_t pos) {
    if (pos >= q->count) {
        printf("\n");
        return;
    }

    data_type elem = queue_at(q, pos);
    printf("[key=%d, val=%d] ", elem.key, elem.value);

    queue_print_recursive(q, pos + 1);
}

void queue_print(const queue* q) {
    if (queue_is_empty(q)) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь (%lu элементов): ", q->count);
    queue_print_recursive(q, 0);
}

void queue_insert(queue* q, const data_type elem) {
    if (q->count >= 100) {
        fprintf(stderr, "Ошибка: очередь переполнена!\n");
        return;
    }

    size_t insert_pos = 0;
    while (insert_pos < q->count) {
        data_type current = queue_at(q, insert_pos);
        if (current.key >= elem.key) {
            break;
        }
        insert_pos++;
    }

    q->count++;

    for (size_t i = q->count - 1; i > insert_pos; i--) {
        data_type temp = queue_at(q, i - 1);
        queue_set(q, i, temp);
    }

    queue_set(q, insert_pos, elem);
}

void queue_erase(queue* q, key_type key) {
    size_t pos = 0;

    while (pos < q->count) {
        data_type current = queue_at(q, pos);
        if (current.key == key) {
            for (size_t i = pos; i < q->count - 1; i++) {
                data_type temp = queue_at(q, i + 1);
                queue_set(q, i, temp);
            }
            q->count--;
            return;
        }
        pos++;
    }

    fprintf(stderr, "Ошибка: элемент с ключом %d не найден!\n", key);
}

iterator queue_begin(queue* q) {
    iterator it;
    it.pos = 0;
    it.cont = q;
    return it;
}

iterator iter_next(iterator it) {
    if (it.pos < it.cont->count) {
        it.pos++;
    }
    return it;
}

iterator iter_prev(iterator it) {
    if (it.pos > 0) {
        it.pos--;
    }
    return it;
}

data_type* iter_deref(iterator it) {
    if (it.pos < it.cont->count) {
        static data_type elem;
        elem = queue_at(it.cont, it.pos);
        return &elem;
    }
    return NULL;
}

bool iter_valid(iterator it) {
    return it.pos < it.cont->count;
}
