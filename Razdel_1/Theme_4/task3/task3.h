#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct SubList {
    int value;
    struct SubList *next;
} SubList;

typedef struct MainList {
    int value;
    SubList *first;
    struct MainList *next;
} MainList;

MainList *List;

void init();
bool isEmptyMain();
bool isEmptySub(MainList *Current);
void showList();
void addSubListToMain();
void addToSub();
void removeSubFromMain();
void removeFromSub();
void searchElement();
void clearList();
void mainMenu();
