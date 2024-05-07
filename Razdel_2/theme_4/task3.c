#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define KEY_NUMBER 10

typedef struct ListNode {
    char key[15];
    struct ListNode* next;
} ListNode;


typedef struct {
    ListNode* head;
    ListNode* tail;
} List;

List* hashTable[TABLE_SIZE];

const char keys[KEY_NUMBER][15] = {"Akhmetgaleev", "Valiev", "Gataullin", "Gavrilov", "Shaidullin",   //0 5 9 2 7
                                   "Bagautdinov", "Abeydullov", "Gromov", "Safiullin", "Frantsuzov"}; //0 7 4 5 0

int getValue(const char* key) {
    int value = 0;
    for (int i = 0; i < strlen(key); i++) {
        value += (int)key[i];
    }
    return value % TABLE_SIZE;
}


bool push(const char *key) {
    int index = getValue(key);
    ListNode* current = hashTable[index] != NULL ? hashTable[index]->head : NULL;
    
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            printf("Элемент с таким ключом уже существует\n");
            return false;
        }
        current = current->next;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = (List*)malloc(sizeof(List));
        hashTable[index]->head = newNode;
        hashTable[index]->tail = newNode;
    } else {
        hashTable[index]->tail->next = newNode;
        hashTable[index]->tail = newNode;
    }
    return true;
}


bool keyFound(const char* key, int* comparisons) {
    int index = getValue(key);
    ListNode* current = hashTable[index] != NULL ? hashTable[index]->head : NULL;
    while (current != NULL) {
        (*comparisons)++;
        if (strcmp(key, current->key) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void pop(const char *key) {
    int index = getValue(key);
    ListNode* current = hashTable[index] != NULL ? hashTable[index]->head : NULL;
    ListNode* prev = NULL;
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            if (prev == NULL) {
                hashTable[index]->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == hashTable[index]->tail) {
                hashTable[index]->tail = prev;
            }
            free(current);
            printf("Элемент успешно удален\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Элемент не найден\n");
}

void showTable() {
    printf("Состояние хеш-таблицы\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d) ", i);
        ListNode* current = hashTable[i] != NULL ? hashTable[i]->head : NULL;
        while (current != NULL) {
            printf("%s ", current->key);
            current = current->next;
        }
        printf("\n");
    }
}

void freeList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            freeList(hashTable[i]->head);
            free(hashTable[i]);
        }
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int comparisons = 0;
    while (true) {
        int n;
        system("clear");
        printf("1 - Добавить элемент в таблицу\n");
        printf("2 - Поиск ключа в таблице\n");
        printf("3 - Вывести состояние таблицы на экран\n");
        printf("4 - Удалить элемент из таблицы\n");
        printf("0 - Выход из программы\n");
        scanf("%d", &n);
        switch (n) {
            case 1: {
                char key[15];
                printf("Введите строку-ключ для добавления: ");
                scanf("%s", key);
                comparisons = 0;
                if (push(key)) {
                    printf("Элемент добавлен\n");
                } else {
                    printf("Не удалось добавить элемент\n");
                }
                break;
            }
            case 2: {
                char key[15];
                printf("Введите строку-ключ для поиска: ");
                scanf("%s", key);
                comparisons = 0;
                if (keyFound(key, &comparisons)) {
                    printf("Элемент найден. Количество сравнений: %d\n", comparisons);
                } else {
                    printf("Элемент не найден. Количество сравнений: %d\n", comparisons);
                }
                break;
            }
            case 3: {
                showTable();
                break;
            }
            case 4: {
                char key[15];
                printf("Введите строку-ключ для удаления: ");
                scanf("%s", key);
                pop(key);
                break;
            }
            case 0: {
                freeHashTable();
                return EXIT_SUCCESS;
            }
            default:
                printf("Неизвестная операция, повторите попытку\n");
                break;
        }
        getchar();
        getchar();
    }
}
