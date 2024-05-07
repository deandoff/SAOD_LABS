#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////////////////////////
void selection_sort(int *array, int size);
void choice_sort(int *array, int size);
int *create_random_array(int n);
void show_array(int *array, int size);
int *copy_array(int *src, int size);
void mainMenu(int **array);
void shell_sort(int *array, int size, int gap);
void heapify(int *array, int size, int i, int *compares, int *changes);
void heap_sort(int *array, int size);
void quick_sort(int left, int right, int *array, int size);
/////////////////////////////////////////////////

void quick_sort(int left, int right, int *array, int size) {
    int i, j, sred, temp;
    int compares = 0;
    int changes = 0;
    
    if (left >= right)
        return;
    
    i = left; 
    j = right;
    sred = array[(left + right) / 2];
    
    do {
        compares++;
        while (array[i] < sred)
            i++;
        compares++;
        while (array[j] > sred)
            j--;
        compares++;
        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++; 
            j--;
            changes++;
        }
        compares++;
    } while (i <= j);
    if (left < j)
        quick_sort(left, j, array, size);
    if (i < right)
        quick_sort(i, right, array, size);
    
    if (left == 0 && right == (size - 1)) {
        show_array(array, size);
        printf("Количество сравнений - %d.\nКоличество перестановок - %d.\n", compares, changes);
    }
}

void heap_sort(int *array, int size) {
    if (array == NULL || size == 0) {
        printf("Массив пуст\n");
        return;
    }
    int compares = 0;
    int changes = 0;
    int *copy = copy_array(array, size);
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(copy, size, i, &compares, &changes);
    }
    for (int i = size - 1; i > 0; i--) {
        int tmp = copy[0];
        copy[0] = copy[i];
        copy[i] = tmp;
        changes++;
        heapify(copy, i, 0, &compares, &changes);
    }
    printf("Количество сравнений - %d.\nКоличество перестановок - %d.\n", compares, changes);
    show_array(copy, size);
    free(copy);
}

void heapify(int *array, int size, int i, int *compares, int *changes) {
    int largest = i; // Инициализируем наибольший элемент как корень

    int left = 2*i+1;
    int right = 2*i+2;

    (*compares)++;
    // Если левый дочерний элемент больше корня
    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    (*compares)++;
    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (right < size && array[right] > array[largest])
        largest = right;

    // Если самый большой элемент не корень
    if (largest != i) {
        int tmp = array[i];
        array[i] = array[largest];
        array[largest] = tmp;
        (*changes)++;

        heapify(array, size, largest, compares, changes);
    }
}


void shell_sort(int *array, int size, int gap) {
    if (array == NULL || size == 0) {
        printf("Массив пуст\n");
        return;
    }
    int i, j;
    int compares = 0;
    int changes = 0;
    int *copy = copy_array(array, size);
    while (gap >= 1) {
        for (i = gap; i < size; i++) {
            int temp = copy[i];
            changes++;
            for (j = i; j >= gap && copy[j - gap] > temp; j -= gap) {
                copy[j] = copy[j - gap];
                compares++;
                changes++;
            }
            copy[j] = temp;
            changes++;
        }
        gap /= 2;
    }
    printf("Количество сравнений - %d.\nКоличество перестановок - %d.\n", compares, changes / 3);
    show_array(copy, size);
    free(copy);
}

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
        printf("7 - Сортировка Шелла\n");
        printf("8 - Пирамидальная сортировка\n");
        printf("9 - Быстрая сортировка\n");
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
                int gaps[] = {1, 4, 10, 23, 57, 132, 301, 701};
                for (int i = 0; i < 8; i++) {
                    printf("\nСортировка с шагом %d:\n", gaps[i]);
                    shell_sort(*array, n, gaps[i]);
                }                
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 8) {
            if (*array != NULL) {
                heap_sort(*array, n);
            } else {
                printf("Массив пуст\n");
            }
        }
        else if (result == 9) {
            if (*array != NULL) {
                int compares = 0;
                int changes = 0;
                int *copy = copy_array(*array, n);
                quick_sort(0, n-1, *array, n);
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