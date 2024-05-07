#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// Структура для представления элемента стека
typedef struct Stack {
    int data;
    struct Stack* next;
} Stack;


Stack* main_stack;
Stack* scnd_stack;

// Прототипы функций
void initStack();
Stack* push(Stack* top, int data);
Stack* pop(Stack* top);
int getRandInt(void);
void moveStack(Stack** source, Stack** destination);
void addFromStack();
void popFromStack();
void popForever();
void popMenu();
void addNew();
void showStack(const Stack* top);
bool isEmpty(const Stack* stack);
void addMenu();
void showMenu();
void emptyMenu();
void freeStack(Stack** stack);
void mainMenu();