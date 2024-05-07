#include "task1.h"

bool isEmpty(){
    return head == NULL;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка: Не удалось выделить память для нового узла\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        head->prev = head;
        head->next = head;
    } else {
        Node* last = head->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = head;
        head->prev = newNode;
    }
}

void displayForward() {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    Node* current = head;
    printf("Прямой просмотр списка: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

void displayBackward() {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    Node* current = head->prev;
    printf("Обратный просмотр списка: ");
    do {
        printf("%d ", current->data);
        current = current->prev;
    } while (current != head->prev);
    printf("\n");
}

Node* searchForward(int key) {
    if (head == NULL) {
        printf("Список пуст\n");
        return NULL;
    }
    Node* current = head;
    do {
        if (current->data == key) {
            printf("%d найден в списке\n", key);
            return current;
        }
        current = current->next;
    } while (current != head);
    printf("%d не найден в списке\n", key);
    return NULL;
}

Node* searchBackward(int key) {
    if (head == NULL) {
        printf("Список пуст\n");
        return NULL;
    }
    Node* current = head->prev;
    do {
        if (current->data == key) {
            printf("%d найден в списке\n", key);
            return current;
        }
        current = current->prev;
    } while (current != head->prev);
    printf("%d не найден в списке\n", key);
    return NULL;
}

void insertAfter(int key, int data) {
    Node* found = searchForward(key);
    if (found == NULL) {
        printf("Не удалось найти элемент %d\n", key);
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = found->next;
    newNode->prev = found;
    found->next->prev = newNode;
    found->next = newNode;
}

void insertBefore(int key, int data) {
    Node* found = searchBackward(key);
    if (found == NULL) {
        printf("Не удалось найти элемент %d\n", key);
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = found;
    newNode->prev = found->prev;
    found->prev->next = newNode;
    found->prev = newNode;

    if (found == head) {
        head = newNode;
    }
}

void deleteNode(int key) {
    Node* found = searchForward(key);
    if (found == NULL) {
        printf("Не удалось найти элемент %d\n", key);
        return;
    }
    if (found == head) {
        head = found->next;
    }
    found->prev->next = found->next;
    found->next->prev = found->prev;
    free(found);
    printf("Элемент %d удален из списка\n", key);
}

void mainMenu() {
    int result = -1;

    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Проверить пустоту списка\n");
        printf("2 - Вывести состояние основного списка\n");
        printf("3 - Добавить элемент в список\n");        
        printf("4 - Удалить элемент из списка\n");
        printf("5 - Найти элемент по значению\n");
        printf("0 - Выход\n");
        printf("Введите номер операции - ");
        scanf("%d", &result);


        int ch, key, value;
        switch (result) {
            case 0:
                return;
            case 1:
                if (!isEmpty()) {
                    printf("Cписок не пуст\n");
                } else {
                    printf("Cписок пуст\n");
                }
                break;
            case 2:
                if (!isEmpty()) {
                    printf("В каком порядке хотите вывести список?\n");
                    printf("0 - В прямом\n");
                    printf("1 - В обратном\n");
                    scanf("%d", &ch);
                    if (ch == 0){
                        displayForward();
                    } else if (ch == 1) {
                        displayBackward();
                    } else {
                        printf("Неизвестная операция");
                    }
                } else {
                    printf("Cписок пуст\n");
                }
                break;
            case 3:
                if (!isEmpty()) {
                    printf("Желаете добавить элемент до или после ключа?\n");
                    printf("0 - До\n");
                    printf("1 - После\n");
                    scanf("%d", &ch);
                    if (ch != 1 && ch != 0) {
                        printf("Неизвестная операция");
                    } else {
                        printf("Введите ключ - \n");
                        scanf("%d", &key);
                        printf("Введите значение - \n");
                        scanf("%d", &value);
                        if (ch == 0) {
                            insertBefore(key, value);
                        } else {
                            insertAfter(key, value);
                        }
                    }
                }
                else {
                    printf("Введите значение - \n");
                    scanf("%d", &value);
                    append(value);
                }
                
                break;
            case 4:
                if (!isEmpty()) {
                    printf("Введите значение дня удаления - \n");
                    scanf("%d", &value);
                    deleteNode(value);                   
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

void freeList() {
    if (!isEmpty()) {
        Node *current = head;
        Node *next;
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }
}

int main() {

    mainMenu();
    freeList();
    return 0;
}