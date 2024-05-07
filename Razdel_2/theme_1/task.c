#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////////////////////////
void selection_sort(int *array, int size);
void choice_sort(int *array, int size);
int *create_random_array(int n);
void show_array(int *array, int size);
int *copy_array(int *src, int size);
void insert_sort(int *array, int size);
void mainMenu(int **array);
/////////////////////////////////////////////////

void selection_sort(int *array, int size) {
    if (array == NULL || size == 0) {
        printf("Массив пуст\n");
        return;
    }
    int compares = 0;
    int changes = 0;
    int *copy = copy_array(array, size);
    for (int i = 0; i < size - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < size; ++j) {
            compares++;
            if (copy[j] < copy[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int tmp = copy[i];
            copy[i] = copy[min_index];
            copy[min_index] = tmp;
            changes++;
        }
    }
    printf("Количество сравнений - %d.\nКоличество перестановок - %d.\n", compares, changes);
    show_array(copy, size);
    free(copy);
}

void insert_sort(int *array, int size) {
    if (array == NULL || size == 0) {
        printf("Массив пуст\n");
        return;
    }
    int compares = 0;
    int changes = 0;
    int *copy = copy_array(array, size);

    for (int i = 1; i < size; i++) {
        int temp = copy[i];
        changes++;
        int j = i - 1;
        while (compares++ && j >= 0 && temp < copy[j]) {
            copy[j + 1] = copy[j];
            changes++;
            j--;
        }
        copy[j + 1] = temp;
        changes++;
    }
    printf("Количество сравнений - %d.\nКоличество перестановок - %d.\n", compares, changes / 3);
    show_array(copy, size);
    free(copy);
}

void choice_sort(int *array, int size) {
    if (array == NULL || size == 0) {
        printf("Массив пуст\n");
        return;
    }

    int compares = 0;
    int changes = 0;
    int *copy = copy_array(array, size);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            compares++;
            if (copy[j] > copy[j+1]) {
                int tmp = copy[j];
                copy[j] = copy[j+1];
                copy[j+1] = tmp;
                changes++;
            }
        }
    }
    printf("Количество сравнений - %d.\nКоличество перестановок - %d.\n", compares, changes);
    show_array(copy, size);
    free(copy);
}

int *create_random_array(int n) {
    srand(time(NULL));

    int *array = (int*)malloc(sizeof(int) * n);
    array[0] = n;

    for(int i = 0; i < n; ++i) {
        array[i] = -10000 + rand() % (10000+10000+1);
    }

    return array;
}

void show_array(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int *copy_array(int *src, int size) {
    int *dst = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        dst[i] = src[i];
    }
    return dst;
}

void mainMenu(int **array) {
    int result = -1;
    int n;
    while (result != 0) {
        system("clear");
        printf("Пожалуйста, выберите необходимую операцию!\n");
        printf("1 - Создать массив\n");
        printf("2 - Очистить массив\n");
        printf("3 - Вывести массив\n");
        printf("4 - Сортировка обменом\n");
        printf("5 - Сортировка вставками\n");
        printf("6 - Сортировка выбором\n");
        printf("7 - 3 сортировки одновременно\n");
        printf("0 - Выход\n");

        printf("Введите номер операции - ");
        scanf("%d", &result);

        if (result == 0) {
            printf("До свидания!\n");
            free(*array);
            *array = NULL;
            return;
        }
        else if (result == 1) {
            if (*array == NULL) {
                printf("Введите количество элементов массива\n");
                scanf("%d", &n);
                *array = create_random_array(n);
                printf("Массив успешно создан\n");
            } else {
                printf("Массив уже создан\n");
            }        
        }
        else if (result == 2) {
            if (*array != NULL) {
                free(*array);
                *array = NULL;
                printf("Массив очищен\n");
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 3) {
            if (*array != NULL) {
                show_array(*array, n);
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 4) {
            if (*array != NULL) {
                choice_sort(*array, n);
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 5) {
            if (*array != NULL) {
                insert_sort(*array, n);
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 6) {
            if (*array != NULL) {
                selection_sort(*array, n);
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 7) {
            if (*array != NULL) {
                printf("\nСОРТИРОВКА ОБМЕНОМ\n");
                choice_sort(*array, n);
                printf("\nСОРТИРОВКА ВСТАВКАМИ\n");
                insert_sort(*array, n);
                printf("\nСОРТИРОВКА ВЫБОРОМ\n");
                selection_sort(*array, n);
            } else {
                printf("Массив пуст\n");
            }
        }
        else {
            printf("Неизвестная операция! Повторите ввод...\n");
        }
        getchar();
        getchar();
    }
}

int main() {
    int *array = NULL;
    mainMenu(&array);
    return 0;
}