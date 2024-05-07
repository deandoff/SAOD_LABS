#include "task3.h"

void initializeList() {
    list.head = FREE;
    list.free_index = 1;
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        list.array[i].next = i + 1;
        list.array[i].data = FREE;
    }
    list.array[ARRAY_SIZE - 1].next = FREE;
}

bool isFull() {
    return list.free_index == FREE;
}

bool isEmpty() {
    return list.head == FREE;
}

void insertBefore(int value, int newValue) {
    if (!isEmpty()) {
        int current = list.head;
        int prev = FREE;
        while (current != FREE && list.array[current].data != value) {
            prev = current;
            current = list.array[current].next;
        }
        if (current != FREE) {
            int index = list.free_index;
            list.free_index = list.array[index].next;
            list.array[index].data = newValue;
            list.array[index].next = current;
            if (prev != FREE) {
                list.array[prev].next = index;
            } else {
                list.head = index;
            }
            printf("Элемент %d успешно добавлен перед элементом %d.\n", newValue, value);
            return;
        }
    }
    printf("Элемент %d не найден.\n", value);
}

void insertAfter(int value, int newValue) {
    if (!isEmpty()) {
        int current = list.head;
        while (current != FREE && list.array[current].data != value) {
            current = list.array[current].next;
        }
        if (current != FREE) {
            int index = list.free_index;
            list.free_index = list.array[index].next;
            list.array[index].data = newValue;
            list.array[index].next = list.array[current].next;
            list.array[current].next = index;
            printf("Элемент %d успешно добавлен после элемента %d.\n", newValue, value);
            return;
        }
    }
    printf("Элемент %d не найден.\n", value);
}

void add(int value) {
    if (!isFull()) {
        if (isEmpty()) {
            int index = list.free_index;
            list.free_index = list.array[index].next;
            list.array[index].data = value;
            list.array[index].next = FREE;
            if (isEmpty()) {
                list.head = index;
            } else {
                int current = list.head;
                while (list.array[current].next != FREE) {
                    current = list.array[current].next;
                }
                list.array[current].next = index;
            }
            printf("Элемент %d успешно добавлен.\n", value);
        }
            else {
            int choice;
            printf("Хотите вставить элемент до или после заданного значения?: ");
            printf("1 - ДО ");
            printf("2 - ПОСЛЕ ");
            scanf("%d", &choice);
            if (choice == 1) {
                int beforeValue;
                printf("Введите значение, перед которым нужно вставить элемент: ");
                scanf("%d", &beforeValue);
                insertBefore(beforeValue, value);
            } else if (choice == 2) {
                int afterValue;
                printf("Введите значение, после которого нужно вставить элемент: ");
                scanf("%d", &afterValue);
                insertAfter(afterValue, value);
            } else {
                printf("Некорректный выбор. Вставка отменена.\n");
            }
        }
    } else {
        printf("Список полон\n");
    }
}


void removeElement(int value) {
    if (!isEmpty()) {
        int current = list.head;
        int prev = FREE;
        while (current != FREE && list.array[current].data != value) {
            prev = current;
            current = list.array[current].next;
        }
        if (current != FREE) {
            if (prev != FREE) {
                list.array[prev].next = list.array[current].next;
            } else {
                list.head = list.array[current].next;
            }
            list.array[current].data = FREE;
            list.array[current].next = list.free_index;
            list.free_index = current;
            printf("Элемент %d успешно удален.\n", value);
        } else {
            printf("Элемент %d не найден.\n", value);
        }
    } else {
        printf("Список пуст.\n");
    }
}

void printList() {
    if (!isEmpty()) {
        int current = list.head;
        printf("Список: ");
        while (current != FREE) {
            printf("%d ", list.array[current].data);
            current = list.array[current].next;
        }
        printf("\n");
    } else {
        printf("Список пуст.\n");
    }
}

int findElement(int value) {
    if (!isEmpty()) {
        int index = list.head;
        while (index != FREE) {
            if (list.array[index].data == value) {
                return index;
            }
            index = list.array[index].next;
        }
    }
    return FREE;
}

void mainMenu() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту списка\n");
        printf("2 - Проверить заполненность списка\n");
        printf("3 - Вывести состояние списка\n");
        printf("4 - Добавить элемент в список\n");
        printf("5 - Удалить элемент из списка\n");
        printf("6 - Найти элемент по значению\n");
        printf("0 - Выход\n");

        printf("Введите номер операции - ");
        scanf("%d", &result);

        if (result == 0) {
            return;
        }
        else if (result == 1) {
            if(!isEmpty()){
                printf("Список не пуст\n");
            }
            else printf("Список пуст\n");
        }
        else if (result == 2) {
            if(!isFull()){
                printf("Список не полон\n");
            }
            else printf("Список полон\n");
        }
        else if (result == 3) {
            if(!isEmpty()){
                printf("Состояние списка:\n");
                printList();
            }
            else printf("Список пуст\n");            
        }
        else if (result == 4) {
            if (!isFull()) {
                int value;
                printf("Введите значение для добавления - ");
                scanf("%d", &value);
                add(value);
            } else printf("Список полон\n");
        }
        else if (result == 5) {
            int value;
            printf("Введите значение для удаления - ");
            scanf("%d", &value);
            removeElement(value); 
        }
        else if (result == 6) {
            int value, elem;
            printf("Введите значение для поиска - ");
            scanf("%d", &value);
            elem = findElement(value);
            if (elem != FREE) {
                printf("Элемент найден на позиции %d\n", elem);
            } else printf("Элемент не найден\n");
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
        getchar(); getchar();
    }
}

int main() {
    initializeList();
    mainMenu();

    return 0;
}