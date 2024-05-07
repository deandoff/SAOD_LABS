#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>


#define ADD_MAX 3       // Максимальное количество элементов для добавления
#define ASCII_A 65      // Код ASCII для символа 'A'
#define ASCII_Z 90      // Код ASCII для символа 'Z'

typedef struct Queue {
    int value;
    struct Queue* next;
} Queue;

Queue* First;
Queue* Last;

void *readInput();
void modulate();
void initQueue();
bool isEmpty();
void push(int value);
void printQueue();
void pop();
void mainMenu();
void freeQueue();
void printQueueChar();