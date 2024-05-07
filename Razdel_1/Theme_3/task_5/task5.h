#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* mainList;
Node* stack;

void init();
Node* createNode(int data);
bool isEmptyMainList();
bool isEmptyStack();
void addAfter(Node* prevNode, int data);
void addToMainList();
void addNewElement(int data);
void moveFromAuxiliaryListToMainList();
void removeFromMainList(int data);
void printMainList();
void printStack();
void clearMainList();
void clearStack();
void mainMenu();
int findElement(int value);