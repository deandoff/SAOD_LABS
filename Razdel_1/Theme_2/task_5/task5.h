#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

typedef struct Queue {
    int First, Last;
    int Queue[ARRAY_SIZE];
    int count;

    
} Queue;

Queue queue;

void initQueue();
void mainMenu();
bool isEmpty();
bool isFull();
void push(int value);
void printQueue();
void pop();