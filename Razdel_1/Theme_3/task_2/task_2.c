#include "task_2.h"

void insert(const void *value, DataType type) {
    if(!isFull()) {
        int i;
        for (i = 0; i < list.size; i++) {
            if (list.array[i].type == INTEGER && type == INTEGER) {
                if (list.array[i].data.intData > *((int*)value)) {
                    break;
                }
            } else {
                continue;
            }
        }
        for (int j = list.size; j > i; j--) {
            list.array[j] = list.array[j - 1];
        }
        list.array[i].type = type;
        if (type == INTEGER) {
            list.array[i].data.intData = *((int*)value);
        }
        list.size++;
    }
}

void pop(const void *value, DataType type) {
    if (!isEmpty()) {
        int i;
        for (i = 0; i < list.size; i++) {
            if (list.array[i].type == INTEGER && type == INTEGER) {
                if (list.array[i].data.intData == *((int*)value)) {
                    break;
                }
            }
        }
        for (int j = i; j < list.size - 1; j++) {
            list.array[j] = list.array[j + 1];
        }
        list.size--;
    }
}

int findElement(const void *value, DataType type) {
    for (int i = 0; i < list.size; i++) {
        if (list.array[i].type == type) {
            if (type == INTEGER && list.array[i].data.intData == *((int*)value)) {
                return i;
            }
        }
    }
    return -1;
}

bool isFull() {
    return list.size == ARRAY_SIZE;
}

bool isEmpty() {
    return list.size == 0;
}

void initList() {
    list.size = 0;
}

void showList() {
    printf("Элементы списка:\n");
    for (int i = 0; i < list.size; i++) {
        if (list.array[i].type == INTEGER) {
            printf("%d ", list.array[i].data.intData);
        }
    }
    printf("\n");
}

void clearList() {
    list.size = 0;
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
        printf("7 - Очистить список\n");
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
                showList(); 
            }
            else printf("Список пуст\n");            
        }
        else if (result == 4) {
            if(!isFull()) {
                int intValue, cnt;
                DataType type;
                printf("Сколько значений хотите добавить? - ");
                scanf("%d", &cnt);
                for (int i = 0; i < cnt; i++) {
                    printf("Введите значение для добавления - ");
                    if (scanf("%d", &intValue) == 1) {
                        type = INTEGER;
                        insert(&intValue, type);
                    }
                }
            }
            else printf("Список переполнен\n");            
        }
        else if (result == 5) {
            if(!isEmpty()) {
                int intValue;
                char strValue[MAX_STRING_LENGTH];
                DataType type;
                printf("Введите значение для удаления - ");
                if (scanf("%d", &intValue) == 1) {
                    type = INTEGER;
                    pop(&intValue, type);
                }
            }
            else printf("Список пуст\n");     
        }
        else if (result == 6) {
            if(!isEmpty()) {
                int intValue;
                int elem;
                char strValue[MAX_STRING_LENGTH];
                DataType type;
                printf("Введите значение для поиска - ");
                if (scanf("%d", &intValue) == 1) {
                    type = INTEGER;
                    elem = findElement(&intValue, type);
                }
                if (elem == -1) {
                    printf("Элемент не найден!\n");
                } else {
                    printf("Элемент найден на позиции %d\n", elem);
                }
            }
            else printf("Список пуст\n");     
        }
        else if (result == 7){
            if (!isEmpty())
            {
                clearList();
            }
            else printf("Список пуст.");
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
        getchar(); getchar();
    }
}

int main(void) {
    initList();
    mainMenu();
    clearList();
    return EXIT_SUCCESS;
}
