#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define KEY_NUMBER 10

bool keyFound(const char* key);
bool push(char **table, const char *key);
void pop(char **table, const char *key);
int getValue(const char* key);
void showTable(char** table);

const char keys[KEY_NUMBER][15] = {"INCLUDE", "DEFINE", "END", "IF", 
                                    "PRAGMA", "CASE", "ENUM", "SIGNED", "CONST", "START"};

bool keyFound(const char* key) {
    for (int i = 0; i < KEY_NUMBER; i++) {
        if (strcmp(key, keys[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool push(char **table, const char *key) {
    int value = 0;
    if (keyFound(key)) {
        value = getValue(key);
        if (strcmp(key, table[value]) != 0) {
            strcpy(table[value], key);
            return true;
        } else {
            printf("Элемент уже был добавлен\n");
        }
    } else {
        printf("Неизвестный ключ\n");
    }
    return false;
}

void pop(char **table, const char *key) {
    int value = getValue(key);
    if (strcmp(key, table[value]) == 0) {
        strcpy(table[value], "");
        printf("Элемент успешно удален\n");
    } else {
        printf("Элемент не найден\n");
    }
}

int getValue(const char* key) {
    int value = 0;
    for (int i = 0; i < strlen(key); i++) {
        value += (int)key[i];
    }
    value %= KEY_NUMBER;
    return value;
}

void showTable(char** table) {
    printf("Состояние хеш-таблицы\n");
    for (int i = 0; i < KEY_NUMBER; i++) {
        printf("%d) %s\n", i, table[i] != NULL ? table[i] : "NULL");
    }
}

int main() {
    char* table[KEY_NUMBER];
    for (int i = 0; i < KEY_NUMBER; i++) {
        table[i] = (char*)malloc(15 * sizeof(char));
    }
    int filled = 0;
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
                if (filled < KEY_NUMBER) {
                    char key[15];
                    printf("Введите строку-ключ для добавления: ");
                    scanf("%s", key);
                    if (push(table, key)) {
                        filled++;
                        printf("Элемент добавлен\n");
                    }
                } else {
                    printf("Таблица переполнена\n");
                }
                break;
            }
            case 2: {
                char key[15];
                printf("Введите строку-ключ для поиска: ");
                scanf("%s", key);
                int value = getValue(key);
                if (strcmp(key, table[value]) == 0) {
                    printf("Элемент %s найден в ячейке со значением %d\n", key, value);
                } else {
                    printf("Элемент не найден\n");
                }
                break;
            }
            case 3: {
                showTable(table);
                break;
            }
            case 4: {
                char key[15];
                printf("Введите строку-ключ для удаления: ");
                scanf("%s", key);
                pop(table, key);
                break;
            }
            case 0: {
                for (int i = 0; i < KEY_NUMBER; i++) {
                    free(table[i]);
                }
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
