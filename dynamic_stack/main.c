#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef void *Pointer;

typedef struct tStack {
    int size;// Текущее количество элементов
    int capacity;// Максимальное количество элементов
    Pointer *start;// Начало массива
} Stack;

/* Создать пустой стек */
void stack_create(Stack *pstack) {
    pstack->start = malloc(sizeof(Pointer));
    if (pstack->start == 0) { exit(1); }
    pstack->capacity = 1;
    pstack->size = 0;
};

/* Уничтожить стек, освободив выделенную память */
void stack_destroy(Stack *pstack) {
    pstack->capacity = 0;
    pstack->size = 0;
    free(pstack->start);
}
//Поменять size и capacity
/* Поместить значение value на вершину стека */
void stack_push(Stack *pstack, Pointer value) {
    pstack->size++;
    if (pstack->size >= pstack->capacity) {
        pstack->start = realloc(pstack->start, pstack->capacity * 2);
        if (pstack->start == NULL) {
            stack_destroy(pstack);
            exit(1);
        }
        pstack->capacity *= 2;
    }
    pstack->start[pstack->size] = value;
}

/* Возвращает количество элементов в стеке (0, если стек пуст) */
size_t stack_size(Stack *pstack) {
    return (pstack->size);
}

/* Снять значение с вершины стека. Если стек пуст, возвращает 0 */
Pointer stack_pop(Stack *pstack) {
    if (pstack->size == 0) { return 0; }
    Pointer res = *(pstack->start + pstack->capacity);
    pstack->start[pstack->size] = 0;
    pstack->size--;
    if (pstack->size >= pstack->capacity / 4 && pstack->capacity >= 4) {
        pstack->start = realloc(pstack->start, pstack->capacity / 2);
        if (pstack->start == NULL) {
            stack_destroy(pstack);
            exit(1);
        }
        pstack->capacity /= 2;
    }
    return (res);
}

/*
 * Возвращает значение с вершины стека, не удаляя его из стека.
 * Если стек пуст, возвращает 0
 */
Pointer stack_peek(Stack *pstack) {
    if (pstack->size == 0) { return 0; }
    Pointer res = *(pstack->start + pstack->capacity);
    return (res);
};

int test() {
    return 0;
}

int main() {
    test();
    Stack* stack;
    stack_create(stack);
    int* primer = malloc(sizeof(int));
    primer[0] = 1;
    stack_push(stack, primer);
    int a = *(stack_peek(stack));
    //assert(primer[0]==a);
    printf('%d, %d', primer[0], a);
    return 0;
}
