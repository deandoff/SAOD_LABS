#include "task5.h"

void initQueue() {
    queue.First = 0;
    queue.Last = 0;
    queue.count = 0;
}

bool isEmpty() {
    return queue.count == 0;
}

bool isFull() {
    return queue.count == ARRAY_SIZE;
}

void push(int value) {
    if (!isFull()){
        queue.Queue[queue.Last] = value;
        queue.Last++;
        if (queue.Last == ARRAY_SIZE) queue.Last = 0;
        queue.count++;
    }
    else {
        printf("Очередь переполнена\n");
    }
}

void printQueue(){
    if(!isEmpty()) {
        int curr = queue.First;
        do {
            printf("%d\t", queue.Queue[curr]);
            curr++;
            if (curr == ARRAY_SIZE) curr = 0;
        }
        while(curr != queue.Last);
    }
    else {
        printf("Очередь пуста\n");
    }
}
void pop() {
    if(!isEmpty()){
        queue.First++;
        if(queue.First == ARRAY_SIZE) queue.First = 0;
        queue.count--;
    }
    else {
        printf("Очередь пуста\n");
    }
}

void mainMenu() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту очереди\n");
        printf("2 - Проверить заполненность очереди\n");
        printf("3 - Добавить элемент в очередь\n");
        printf("4 - Удалить элемент из очереди\n");
        printf("5 - Вывести состояние очереди\n");        
        printf("0 - Выйти из программы\n");

        printf("Введите номер операции - ");
        scanf("%d", &result);

        if (result == 0) {
            printf("До свидания!\n");
            return;
        }
        else if (result == 1) {
            if(!isEmpty()){
                printf("Очередь не пуста\n");
            }
            else printf("Очередь пуста\n");
        }
        else if (result == 2) {
            if(!isFull()){
                printf("Очередь не полная\n");
            }
            else printf("Очередь полная\n");
        }
        else if (result == 3) {
            if(!isFull()) {
                int value;
                int elem;
                printf("Сколько элементов хотите добавить?\n");
                scanf("%d", &elem);
                for (int i = 0; i < elem; ++i) {
                    if (!isFull()) {
                        printf("\nВведите желаемый элемент - ");
                        scanf("%d", &value);
                        push(value);
                    }
                    else break;
                }
                printf("Элементы успешно добавлены\n");
            }
            else printf("Очередь переполнена\n");
        }
        else if (result == 4) {
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
        else if (result == 5) {
            printf("Текущее состояние очереди:\n");
            printQueue();
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
        getchar(); getchar();
    }
}

int main(void){
    initQueue();
    mainMenu();
    return 0;
}