#include "task7.h"

// Функция для считывания ввода
void *readInput() {
    char key;
    printf("Нажмите <q> или <Q> для выхода из режима моделирования очереди\n");
    while (1) {
        scanf(" %c", &key);
        if (key == 'q' || key == 'Q') {
            printf("Программа завершает работу...\n");
            freeQueue();
            exit(0);
        }
    } 
}

// Функция для моделирования работы очереди
void modulate(){
    printf("\nМОДЕЛИРОВАНИЕ ОЧЕРЕДИ\n");
    char key = '\0';
    int n, x;
    while (1) {
        sleep(1);
        if (isEmpty()) 
            x = 1;
        else 
            x = (rand() % 2 == 0);
        
        if (x == 1) { // добавление
            n = rand() % ADD_MAX + 1;
            printf("\nГенерация и добавление %d элемент(ов) в очередь...\n", n);
            sleep(1);
            for (int i = 0; i < n; i++) {
                char newElement = ASCII_A + rand() % (ASCII_Z - ASCII_A + 1); // Случайный символ от 'A' до 'Z'
                push(newElement);
            }
        }
        else { // удаление
            n = rand() % ADD_MAX + 1;
            printf("\nИзвлечение %d элемента(ов) из очереди...\n", n);
            sleep(1);
            for (int i = 0; i < n; i++)
                if (!isEmpty()) pop();
        }
        printf("Состояние очереди: ");
        printQueueChar();
    }
}

//Инициализация очереди
void initQueue() {
    First = malloc(sizeof(Queue));
    if (First == NULL) {
        exit(1);
    }
    First->next = NULL;
    Last = First;
}

//Проверка на пустоту
bool isEmpty() {
    return First->next == NULL;
}

//Добавление в очередь
void push(int value) {
    Queue* curr = malloc(sizeof(Queue));
    curr->value = value;
    curr->next = NULL;
    Last->next = curr;
    Last = curr;
}

//Вывод состояния
void printQueue(){
    if(!isEmpty()) {
        Queue* curr;
        curr = First->next;
        while (curr!=NULL)
        {
            printf("%d\t", curr->value);
            curr = curr->next;
        }
        
    }
    else {
        printf("Очередь пуста\n");
    }
}

//Вывод состояния в виде символов ASCII (для моделирования)
void printQueueChar(){
    if(!isEmpty()) {
        Queue* curr;
        curr = First->next;
        while (curr!=NULL)
        {
            printf("%c\t", (char)curr->value);
            curr = curr->next;
        }
        
    }
    else {
        printf("Очередь пуста\n");
    }
}

//Удаление из очереди
void pop() {
    if(!isEmpty()){
        Queue* curr;
        curr = First->next;
        First->next = curr->next;
        if(isEmpty()){
            Last = First;
        }
        free(curr);
    }
    else {
        printf("Очередь пуста\n");
    }
}


//Меню главной программы
void mainMenu() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту очереди\n");
        printf("2 - Добавить элемент в очередь\n");
        printf("3 - Удалить элемент из очереди\n");
        printf("4 - Вывести состояние очереди\n");        
        printf("0 - Назад\n");

        printf("Введите номер операции - ");
        scanf("%d", &result);

        if (result == 0) {
            return;
        }
        else if (result == 1) {
            if(!isEmpty()){
                printf("Очередь не пуста\n");
            }
            else printf("Очередь пуста\n");
        }
        else if (result == 2) {
            int value;
            int elem;
            printf("Сколько элементов хотите добавить?\n");
            scanf("%d", &elem);
            for (int i = 0; i < elem; ++i) {
                printf("\nВведите желаемый элемент - ");
                scanf("%d", &value);
                push(value);
            }
            printf("Элементы успешно добавлены\n");
        }
        else if (result == 3) {
            if (!isEmpty()) {
                int elem;
                printf("Сколько элементов хотите удалить?\n");
                scanf("%d", &elem);
                for (int i = 0; i < elem; ++i) {
                    if (!isEmpty()){
                        pop();
                    }
                    else break;
                }
                printf("Элементы успешно удалены\n");
            }
            else printf("Очередь пуста\n");
        }
        else if (result == 4) {
            printf("Текущее состояние очереди:\n");
            printQueue();
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
        getchar(); getchar();
    }
}

//Функция освобождения памяти
void freeQueue(){
    Queue *curr;
    while (First!=NULL)
    {
        curr = First;
        First = First->next;
        free(curr);
    }
    
}

//Стартовое меню
void choice() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Запустить основную программу\n");
        printf("2 - Запустить модолеривание работы очереди\n");
        printf("0 - Выйти из программы\n");

        printf("Введите номер операции - ");
        scanf("%d", &result);

        if (result == 0) {
            printf("До свидания!\n");
            return;
        }
        else if (result == 1){
            mainMenu();
        }
        else if (result == 2){
            pthread_t inputThread; 
            if (pthread_create(&inputThread, NULL, readInput, NULL) != 0) {
                fprintf(stderr, "Ошибка: Не удалось создать поток для считывания ввода\n");
                return;
            }
            modulate();
            pthread_join(inputThread, NULL);        
        }
    }
}


int main() {

    srand(time(NULL));
    initQueue();
    choice();
    freeQueue();

    return EXIT_SUCCESS;
}