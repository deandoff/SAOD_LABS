#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;

bool isEmpty();
Node* createNode(int data);
void append(int data);
void displayForward();
void displayBackward();
Node* searchForward(int key);
Node* searchBackward(int key);
void insertAfter(int key, int data);
void insertBefore(int key, int data);
void deleteNode(int key);
void mainMenu();
void freeList();