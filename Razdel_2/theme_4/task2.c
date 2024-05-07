#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // Размер хеш-таблицы
#define KEY_NUMBER 10 // Количество ключей в исходном наборе

bool keyFound(const char* key, char** table, int* comparisons);
bool push(char **table, const char *key, int* comparisons);
void pop(char **table, const char *key);
int getValue(const char* key);
void showTable(char** table);

const char keys[KEY_NUMBER][15] = {"Akhmetgaleev", "Valiev", "Gataullin", "Gavrilov", "Shaidullin",   //0 5 9 2 7
                                   "Bagautdinov", "Abeydullov", "Gromov", "Safiullin", "Frantsuzov"}; //0 7 4 5 0


bool keyFound(const char* key, char** table, int* comparisons) {
    int value = getValue(key);
    int i = 0;
    while (table[value] != NULL) {
        (*comparisons)++;
        if (strcmp(key, table[value]) == 0) {
            return true;
        }
        i++;
        value = (getValue(key) + i) % TABLE_SIZE;
    }
    return false;
}

bool push(char **table, const char *key, int* comparisons) {
    int value = getValue(key);
    int i = 0;
    while (table[value] != NULL) {
        (*comparisons)++;
        if (strcmp(key, table[value]) == 0) {
            printf("Элемент уже присутствует в таблице\n");
            return false;
        }
        i++;
        value = (getValue(key) + i) % TABLE_SIZE;
    }
    if (table[value] == NULL) {
        table[value] = (char*)malloc(15 * sizeof(char));
        strcpy(table[value], key);
        return true;
    }
    return false;
}


void pop(char **table, const char *key) {
    int value = getValue(key);
    int i = 0;
    while (table[value] != NULL) {
        if (strcmp(key, table[value]) == 0) {
            free(table[value]);
            table[value] = NULL;
            printf("Элемент успешно удален\n");
            return;
        }
        i++;
        value = (getValue(key) + i) % TABLE_SIZE;
    }
    printf("Элемент не найден\n");
}

int getValue(const char* key) {
    int value = 0;
    for (int i = 0; i < strlen(key); i++) {
        value += (int)key[i];
    }
    return value % TABLE_SIZE;
}

void showTable(char** table) {
    printf("Состояние хеш-таблицы\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d) %s\n", i, table[i] != NULL ? table[i] : "NULL");
    }
}

int main() {
    char* table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
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
                if (push(table, key, &comparisons)) {
                    printf("Элемент добавлен. Количество сравнений: %d\n", comparisons);
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
                if (keyFound(key, table, &comparisons)) {
                    printf("Элемент найден. Количество сравнений: %d\n", comparisons);
                } else {
                    printf("Элемент не найден. Количество сравнений: %d\n", comparisons);
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
                for (int i = 0; i < TABLE_SIZE; i++) {
                    if (table[i] != NULL) {
                        free(table[i]);
                    }
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
