#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define ARRAY_SIZE 6
#define FREE -1

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    int next;
} Node;

typedef struct LinkedList {
    Node array[ARRAY_SIZE];
    int head;
    int free_index;
} LinkedList;

LinkedList list;


void initializeList();
bool isFull();
bool isEmpty();
void add(int value);
void removeElement(int value);
void printList();
int findElement(int value);

#endif /* LINKEDLIST_H */