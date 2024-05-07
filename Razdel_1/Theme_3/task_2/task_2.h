#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 50

typedef enum {
    INTEGER,
} DataType;

typedef struct Node {
    DataType type;
    union {
        int intData;
    } data;
} Node;

typedef struct OrderedLinkedList {
    Node array[ARRAY_SIZE];
    int size;
} OrderedLinkedList;

OrderedLinkedList list;

void insert(const void *value, DataType type);
void pop(const void *value, DataType type);
bool isFull();
bool isEmpty();
void initList();
void showList();
void clearList();
void mainMenu();
int findElement(const void *value, DataType type);