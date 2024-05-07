#include "task4.h"

// Функция для добавления элемента в стек
Stack* push(Stack* top, int data) {
    Stack* ptr = malloc(sizeof(Stack));
    if (ptr == NULL) {
        return NULL;
    }
    ptr->data = data;
    ptr->next = top;
    return ptr;
}

// Функция для удаления элемента из стека
Stack* pop(Stack* top) {
    if (isEmpty(top)) {
        return NULL;
    }
    printf("Элемент %d был успешно удален.\n", top->data);
    Stack* ptr_next = top->next;
    free(top);
    return ptr_next;
}

// Функция для перемещения элемента из одного стека в другой
void moveStack(Stack** source, Stack** destination) {
    if (isEmpty(*source)) {
        return;
    }

    Stack* temp = *source;
    *source = (*source)->next;

    temp->next = *destination;
    *destination = temp;
}

// Функция для генерации случайного целого числа
int getRandInt(void) {
    static int initialized = 0;
    if (!initialized) {
        initialized = 1;
    }
    return rand();
}

void initStack() {
    main_stack = NULL;
    scnd_stack = NULL;
}

// Функция для добавления элементов из вспомогательного стека в главный
void addFromStack() {
    int counter = 0;
    system("clear");
    printf("Сколько элементов хотите переместить?\n");
    printf("0 - Назад\n");
    scanf("%d", &counter);
    if (counter == 0) {
        return;
    }
    else if (counter < 0) {
        printf("Введено некорректное значение! Повторите попытку...\n");
        getchar();
        getchar();
        addFromStack();
        return;
    }
    else {
        for (int i = 0; i < counter; ++i) {
            if (!isEmpty(scnd_stack)) {
                moveStack(&scnd_stack, &main_stack);
            }
            else {
                printf("Все элементы были перемещены\n");
                break;
            }
        }
        printf("Элементы перемещены успешно!\n");
        getchar();
        getchar();
    }
}

// Функция для удаления элементов из главного стека
void popFromStack() {
    int counter = 0;
    system("clear");
    printf("Сколько элементов хотите переместить?\n");
    printf("0 - Назад\n");
    scanf("%d", &counter);
    if (counter == 0) {
        return;
    }
    else if (counter < 0) {
        printf("Введено некорректное значение! Повторите попытку...\n");
        getchar();
        getchar();
        popFromStack();
        return;
    }
    else {
        for (int i = 0; i < counter; ++i) {
            if (!isEmpty(main_stack)) {
                moveStack(&main_stack, &scnd_stack);
            }
            else {
                printf("Все элементы были перемещены\n");
                break;
            }
        }
        printf("Элементы перемещены успешно!\n");
        getchar();
        getchar();
    }
}

// Функция для окончательного удаления элементов из главного стека
void popForever() {
    int counter = 0;
    system("clear");
    printf("Сколько элементов хотите удалить?\n");
    printf("0 - Назад\n");
    scanf("%d", &counter);
    if (counter == 0) {
        return;
    }
    else if (counter < 0) {
        printf("Введено некорректное значение! Повторите попытку...\n");
        getchar();
        getchar();
        return;
    }
    else {
        for (int i = 0; i < counter; ++i) {
            if (!isEmpty(main_stack)) {
                main_stack = pop(main_stack);
            }
            else {
                printf("Все элементы перемещены\n");
                break;
            }
        }
    }
    getchar();
    getchar();
}

// Функция для отображения меню удаления элементов
void popMenu() {
    int result = 0;
    system("clear");
    printf("Желаете окончательно удалить элементы или переместить в вспомогательный стек?\n");
    printf("1 - Удалить окончательно\n");
    printf("2 - Переместить в стек\n");
    printf("0 - Назад\n");

    printf("Выберите операцию - ");
    scanf("%d", &result);

    if (result == 1) {
        popForever();
    }
    else if (result == 2) {
        popFromStack();
    }
    else if (result == 0) {
        return;
    }
    else {
        printf("Неизвестная операция! Повторите ввод...\n");
    }

    getchar();
    getchar();
}

// Функция для добавления новых элементов в стек
void addNew() {
    int counter = 0;
    system("clear");
    printf("Сколько элементов хотите добавить?\n");
    printf("0 - Назад\n");
    scanf("%d", &counter);
    if (counter == 0) {
        return;
    }
    else if (counter < 0) {
        printf("Введено некорректное значение! Повторите попытку...\n");
        getchar();
        return;
    }
    else {
        int result = 0;
        system("clear");
        printf("Желаете добавить вручную или автоматически?\n");
        printf("1 - Вручную\n");
        printf("2 - Автоматически\n");

        printf("Выберите операцию - ");
        scanf("%d", &result);

        if (result == 1) {
            for (int i = 0; i < counter; ++i) {
                int data;
                printf("Введите элемент для добавления - ");
                scanf("%d", &data);
                main_stack = push(main_stack, data);
                if (main_stack != NULL) {
                    printf("Элемент %d был успешно добавлен\n", data);
                }
                else {
                    printf("Ошибка выделения памяти\n");
                }
            }
        }
        else if (result == 2) {
            for (int i = 0; i < counter; ++i) {
                int data = getRandInt();
                main_stack = push(main_stack, data);
                if (main_stack != NULL) {
                    printf("Элемент %d был успешно добавлен\n", data);
                }
                else {
                    printf("Ошибка выделения памяти\n");
                }
            }
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
        getchar();
    }
}

// Функция для отображения содержимого стека
void showStack(const Stack* top) {
    if (isEmpty(top)) {
        printf("Стек пуст.\n");
    }
    else {
        const Stack* current = top;
        while (current) {
            printf("%d\n", current->data);
            current = current->next;
        }
    }
}

// Функция для отображения меню добавления элементов и выбора операций
void addMenu() {
    int result = 0;
    system("clear");
    printf("Желаете добавить новые элементы или взять из вспомогательного стека?\n");
    printf("1 - Добавить новые\n");
    printf("2 - Взять из стека\n");
    printf("0 - Назад\n");

    printf("Выберите операцию - ");
    scanf("%d", &result);

    if (result == 1) {
        addNew();
    }
    else if (result == 2) {
        if (isEmpty(scnd_stack)) {
            printf("Вспомогательный стек пуст.\n");
        }
        else {
            addFromStack();
        }
    }
    else if (result == 0) {
        return;
    }
    else {
        printf("Неизвестная операция! Повторите ввод...\n");
    }

    getchar();
    getchar();
}

// Функция для отображения содержимого стеков (главного или вспомогательного)
void showMenu() {
    int result = 0;
    system("clear");
    printf("Состояние какого стека вы хотите вывести?\n");
    printf("1 - Главный стек\n");
    printf("2 - Вспомогательный стек\n");
    printf("0 - Назад\n");

    printf("Выберите стек - ");
    scanf("%d", &result);

    if (result == 1) {
        printf("\nСостояние главного стека:\n");
        showStack(main_stack);
    }
    else if (result == 2) {
        printf("\nСостояние вспомогательного стека:\n");
        showStack(scnd_stack);
    }
    else if (result == 0) {
        return;
    }
    else {
        printf("Неизвестная операция! Повторите ввод...\n");
    }

    getchar();
    getchar();
}

// Функция для проверки пустоты стека
void emptyMenu() {
    int result = 0;
    system("clear");
    printf("Пустоту какого стека вы хотите проверить?\n");
    printf("1 - Главный стек\n");
    printf("2 - Вспомогательный стек\n");
    printf("0 - Назад\n");

    printf("Выберите стек - ");
    scanf("%d", &result);

    if (result == 1) {
        if (isEmpty(main_stack)) {
            printf("Главный стек пуст.\n");
        }
        else {
            printf("Главный стек не пуст.\n");
        }
    }
    else if (result == 2) {
        if (isEmpty(scnd_stack)) {
            printf("Вспомогательный стек пуст.\n");
        }
        else {
            printf("Вспомогательный стек не пуст.\n");
        }
    }
    else if (result == 0) {
        return;
    }
    else {
        printf("Неизвестная операция! Повторите ввод...\n");
    }

    getchar();
    getchar();
}

void freeStack(Stack** stack) {
    while (*stack != NULL) {
        Stack* temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
    *stack = NULL;
}

bool isEmpty(const Stack* stack) {
    return stack == NULL;
}

// Главное меню программы
void mainMenu() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту стека\n");
        printf("2 - Добавить элемент в стек\n");
        printf("3 - Удалить элемент из стека\n");
        printf("4 - Вывести состояние стека\n");
        printf("0 - Выйти из программы\n");

        printf("Введите номер операции - ");
        scanf("%d", &result);

        if (result == 0) {
            printf("До свидания!\n");
            return;
        }
        else if (result == 1) {
            emptyMenu();
        }
        else if (result == 2) {
            addMenu();
        }
        else if (result == 3) {
            if (isEmpty(main_stack)) {
                printf("В стеке нет элементов.\n");
            }
            else {
                popMenu();
            }
        }
        else if (result == 4) {
            showMenu();
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
    }
}

int main(void) {
    srand(time(NULL));
    printf("Программа запущена.\n");
    initStack();
    mainMenu();
    printf("Программа завершена.\n");
    freeStack(&main_stack);
    freeStack(&scnd_stack);
    return 0;
}
