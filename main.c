#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"
#include "sort_queue.h"
#include <stdio.h>
#include <locale.h>

void input_recursive(queue* q, int count, int current) {
    if (current > count) {
        return;
    }

    printf("Элемент %d: введите key и value: ", current);
    data_type elem;

    if (scanf("%d %d", &elem.key, &elem.value) != 2) {
        fprintf(stderr, "Ошибка ввода!\n");
        return;
    }

    queue_push_back(q, elem);
    input_recursive(q, count, current + 1);
}

void test_standard() {
    printf("\nТЕСТ 1: Стандартный случай (10 элементов) \n");
    queue q;
    queue_create(&q);

    data_type test_data[] = {
        {50, 500}, {30, 300}, {80, 800}, {20, 200}, {90, 900},
        {10, 100}, {70, 700}, {40, 400}, {60, 600}, {25, 250}
    };

    for (int i = 0; i < 10; i++) {
        queue_push_back(&q, test_data[i]);
    }

    printf("ДО сортировки:\n");
    queue_print(&q);

    printf("\nПроцедура: вставка упорядоченного элемента\n");
    data_type new_elem = { 55, 550 };
    printf("Вставляем элемент: key=%d, value=%d\n", new_elem.key, new_elem.value);
    queue_insert(&q, new_elem);
    printf("После вставки:\n");
    queue_print(&q);

    printf("\nПрименяем сортировку (сортировка вставками, рекурсивно):\n");
    sort_queue(&q);

    printf("ПОСЛЕ сортировки:\n");
    queue_print(&q);
}

void test_empty() {
    printf("\n ТЕСТ 2: Пустая очередь \n");
    queue q;
    queue_create(&q);

    printf("Проверка пустой очереди:\n");
    queue_print(&q);
    printf("Размер: %lu\n", queue_size(&q));
    printf("is_empty: %s\n", queue_is_empty(&q) ? "true" : "false");

    printf("\nПробуем вставить в пустую очередь:\n");
    data_type elem = { 100, 1000 };
    queue_insert(&q, elem);
    queue_print(&q);

    printf("Применяем сортировку на очереди с 1 элементом:\n");
    sort_queue(&q);
    queue_print(&q);
}

void test_single() {
    printf("\n ТЕСТ 3: Один элемент \n");
    queue q;
    queue_create(&q);

    data_type elem = { 42, 420 };
    queue_push_back(&q, elem);

    printf("ДО сортировки (1 элемент):\n");
    queue_print(&q);

    printf("\nПрименяем сортировку:\n");
    sort_queue(&q);

    printf("ПОСЛЕ сортировки:\n");
    queue_print(&q);
}

void test_sorted() {
    printf("\n ТЕСТ 4: Уже отсортированная очередь \n");
    queue q;
    queue_create(&q);

    data_type sorted_data[] = {
        {10, 100}, {20, 200}, {30, 300}, {40, 400}, {50, 500}
    };

    for (int i = 0; i < 5; i++) {
        queue_push_back(&q, sorted_data[i]);
    }

    printf("ДО сортировки (уже отсортирована):\n");
    queue_print(&q);

    printf("\nПрименяем сортировку:\n");
    sort_queue(&q);

    printf("ПОСЛЕ сортировки:\n");
    queue_print(&q);
}

void test_iterators() {
    printf("\n ТЕСТ 5: Работа с итераторами \n");
    queue q;
    queue_create(&q);

    data_type data[] = { {50, 500}, {30, 300}, {80, 800} };
    for (int i = 0; i < 3; i++) {
        queue_push_back(&q, data[i]);
    }

    printf("Проход по очереди с помощью итератора (вперёд):\n");
    iterator it = queue_begin(&q);
    int pos = 0;
    while (iter_valid(it)) {
        data_type* elem = iter_deref(it);
        printf("Позиция %d: key=%d, value=%d\n", pos, elem->key, elem->value);
        it = iter_next(it);
        pos++;
    }

    printf("\nПроход в обратном направлении с итератором:\n");
    it = queue_begin(&q);
    it.pos = q.count - 1;
    while (it.pos < q.count) {
        data_type* elem = iter_deref(it);
        printf("Позиция %lu: key=%d, value=%d\n", it.pos, elem->key, elem->value);
        if (it.pos == 0) break;
        it = iter_prev(it);
    }
}

int main() {
    setlocale(LC_ALL, "");

    test_standard();
    test_empty();
    test_single();
    test_sorted();
    test_iterators();

    return 0;
}
