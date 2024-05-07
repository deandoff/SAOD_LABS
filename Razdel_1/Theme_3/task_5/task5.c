#include "task5.h"

void init() {
    mainList = NULL;
    stack = NULL;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

bool isEmptyMainList(){
    return mainList == NULL;
}

bool isEmptyStack(){
    return stack == NULL;
}

void addAfter(Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Ошибка: предыдущий узел не может быть NULL.\n");
        return;
    }
    Node* newNode = createNode(data);
    if (newNode != NULL) {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}

void addToMainList() {
    printf("Что вы хотите сделать?\n");
    printf("1. Добавить новый элемент\n");
    printf("2. Переместить элемент с вершины стека\n");
    int data;
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n');

    switch (choice) {
        case 1:
            printf("Введите элемент для добавления - ");
            scanf("%d", &data);
            addNewElement(data);
            break;
        case 2:
            moveFromAuxiliaryListToMainList();
            break;
        default:
            printf("Некорректный выбор. Оставляем основной список без изменений.\n");
            break;
    }
}

void addNewElement(int data) {
    int choice;
    printf("Куда вы хотите вставить элемент %d?\n", data);
    printf("1. Перед определенным значением\n");
    printf("2. После определенного значения\n");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (mainList == NULL) {
        mainList = createNode(data);
        printf("Новый элемент %d успешно добавлен в основной список.\n", data);
        return;
    }

    int targetValue;
    printf("Введите значение, перед/после которого хотите вставить элемент - ");
    scanf("%d", &targetValue);
    while (getchar() != '\n');

    Node* current = mainList;
    Node* prev = NULL;
    bool inserted = false;

    while (current != NULL) {
        if (choice == 1 && current->data == targetValue) {
            Node* newNode = createNode(data);
            if (prev == NULL) {
                newNode->next = mainList;
                mainList = newNode;
            } else {
                newNode->next = current;
                prev->next = newNode;
            }
            printf("Элемент %d успешно добавлен перед значением %d.\n", data, targetValue);
            inserted = true;
            break;
        } else if (choice == 2 && current->data == targetValue) {
            Node* newNode = createNode(data);
            newNode->next = current->next;
            current->next = newNode;
            printf("Элемент %d успешно добавлен после значения %d.\n", data, targetValue);
            inserted = true;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!inserted) {
        printf("Ошибка: Элемент с заданным значением не найден в основном списке.\n");
    }
}



void moveFromAuxiliaryListToMainList() {
    if (stack == NULL) {
        printf("Стек пуст. Нет элементов для перемещения.\n");
        return;
    }

    Node* temp = stack;
    stack = stack->next;

    temp->next = mainList;
    mainList = temp;
    printf("Элемент с вершины стека успешно перемещен в основной список.\n");
}


void removeFromMainList(int data) {
    Node* current = mainList;
    Node* prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        printf("Элемент %d найден. Что вы хотите сделать с ним?\n", data);
        printf("1. Удалить элемент полностью\n");
        printf("2. Переместить элемент во вспомогательный список (стек)\n");

        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                if (prev == NULL) {
                    mainList = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                printf("Элемент %d успешно удален из основного списка.\n", data);
                break;
            case 2:
                if (prev == NULL) {
                    mainList = current->next;
                } else {
                    prev->next = current->next;
                }
                current->next = stack;
                stack = current;
                printf("Элемент %d перемещен во вспомогательный список (стек).\n", data);
                break;
            default:
                printf("Некорректный выбор. Оставляем элемент в основном списке.\n");
                break;
        }
    } else {
        printf("Элемент %d не найден в основном списке.\n", data);
    }
}

void printMainList() {
    Node* current = mainList;
    printf("Основной список: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


void printStack() {
    Node* current = stack;
    printf("Вспомогательный стек: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void clearMainList() {
    Node* current = mainList;
    Node* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    mainList = NULL;
}

int findElement(int value) {
    Node* current = mainList;
    int index = 1;

    while (current != NULL) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

void clearStack() {
    Node* current = stack;
    Node* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    stack = NULL;
}

void mainMenu() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту основного списка\n");
        printf("2 - Проверить пустоту стека\n");
        printf("3 - Вывести состояние основного списка\n");
        printf("4 - Вывести состояние стека\n");
        printf("5 - Добавить элемент в основной список\n");        
        printf("6 - Удалить элемент из основного списка\n");
        printf("7 - Найти элемент по значению\n");
        printf("0 - Выход\n");
        printf("Введите номер операции - ");
        scanf("%d", &result);

        switch (result) {
            case 0:
                return;
            case 1:
                if (!isEmptyMainList()) {
                    printf("Основной список не пуст\n");
                } else {
                    printf("Основной список пуст\n");
                }
                break;
            case 2:
                if (!isEmptyStack()) {
                    printf("Стек не пуст\n");
                } else {
                    printf("Стек пуст\n");
                }
                break;
            case 3:
                if (!isEmptyMainList()) {
                    printMainList();
                } else {
                    printf("Основной список пуст\n");
                }
                break;
            case 4:
                if (!isEmptyStack()) {
                    printStack();
                } else {
                    printf("Стек пуст\n");
                }
                break;
            case 5:
                addToMainList();
                break;
            case 6:
                if (!isEmptyMainList()) {
                    int value;
                    printf("Введите значение для удаления - ");
                    scanf("%d", &value);
                    removeFromMainList(value);
                } else {
                    printf("Основной список пуст\n");
                }
                break;
            case 7:
                if (!isEmptyMainList()) {
                    int value;
                    printf("Введите значение для поиска - ");
                    scanf("%d", &value);
                    int position = findElement(value);
                    if (position != -1) {
                        printf("Элемент найден на позиции %d в основном списке\n", position);
                    } else {
                        printf("Элемент не найден в основном списке\n");
                    }
                } else {
                    printf("Основной список пуст\n");
                }
                break;
            default:
                printf("Неизвестная операция! Повторите ввод...\n");
                break;
        }
        getchar();
        getchar();
    }
}

int main() {
    init();

    mainMenu();
    clearStack();
    clearMainList();

    return 0;
}