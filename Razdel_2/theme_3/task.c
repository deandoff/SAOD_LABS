#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////////////////////////
typedef struct List {
    int key;
    struct List *next;
    struct List *tail;
} List;

void show_array(int *array, int size);
int *copy_array(int *src, int size);
void mainMenu(int **array);
void pocketSortNoArray(int *array, int n);
void pocketSortWithArray(int *array, int n);
int *create_array(int n, int num);
void clearList(List *list);
int *listToArray(List *list, int n);
List *combine(List *list, int n);
void generalPocketSort(int *array, int n);
void radixSort(int *array, int n);
/////////////////////////////////////////////////
void radixSort(int *array, int n) {
    int *copy = copy_array(array, n);
    int max_key = n - n / 3;
    int k = 0, temp = max_key;
    while (temp != 0) {
        temp = temp / 10;
        k++;
    }
    printf("Количество разрядов - %d\n", k);
    int x, _max;
    List *ls = NULL;
    for (int i = 1; i <= k ; i++) {
        ls = (List *)malloc(max_key * sizeof(List));

        for (int init = 0; init < max_key; init++) {
            ls[init].key = -1;
            ls[init].next = NULL;
            ls[init].tail = NULL;
        }

        for (int j = 0; j < n; j++) {
            x = copy[j];
            for (int z = 1; z < i; z++)
                x = x / 10;
            x = x % 10;
            
            if (ls[x].key == -1)
                ls[x].key = copy[j];
            else if (ls[x].next == NULL) {
                ls[x].next = (List *)malloc(sizeof(List));;
                ls[x].tail = ls[x].next;
                ls[x].next -> key = copy[j];
            }
            else if (ls[x].tail->next == NULL) {
                ls[x].tail -> next = (List *)malloc(sizeof(List));;
                ls[x].tail -> next -> key = copy[j];
                ls[x].tail = ls[x].tail -> next;
            }
        }
        _max = max_key;
        max_key = 10;
        List *head = combine(ls, n);
        max_key = _max;
        copy = listToArray(head, n);
        clearList(head);
        head = NULL;
        printf("Сортировка по разряду %d:\n", i);
        show_array(copy, n);
        free(ls);
    }
    free(copy);
}


void generalPocketSort(int *array, int n) {
    int max_key = n - n / 3;
    int *copy = copy_array(array, n);
    List *ls = (List *)malloc(max_key * sizeof(List));

    for (int i = 0; i < max_key; i++) {
        ls[i].key = -1;
        ls[i].next = NULL;
        ls[i].tail = NULL;
    }

    for (int i = 0; i < n; i++) {
        if (ls[copy[i]].key == -1) ls[copy[i]].key = copy[i];

        else if (ls[copy[i]].next == NULL) {
            ls[copy[i]].next = (List *)malloc(sizeof(List));;
            ls[copy[i]].tail = ls[copy[i]].next;
            ls[copy[i]].next->key = copy[i];
        }

        else if (ls[copy[i]].tail->next == NULL) {
            ls[copy[i]].tail->next = (List *)malloc(sizeof(List));;
            ls[copy[i]].tail->next->key = copy[i];
            ls[copy[i]].tail = ls[copy[i]].tail->next;
        }
    }
    
    List *head = combine(ls, n);
    copy = listToArray(head, n);
    clearList(head);
    head = NULL;
    show_array(copy, n);
    free(copy);
    free(ls);
}

List *combine(List *list, int n) {
    int max_key = n - n / 3;
    List *head = (List*)malloc(sizeof(List));
    head -> key = list[0].key;
    head -> next = list[0].next;
    head -> tail = list[0].tail;
    List *current = head;
    for (int i = 0; i < max_key - 1; i++) {
        if (list[i].tail != NULL)
            current = list[i].tail;
        current -> next = (List*)malloc(sizeof(List));
        current = current -> next;
        current -> key = list[i + 1].key;
        current -> next = list[i + 1].next;
        current -> tail = list[i + 1].tail;
    }
    return head;
}

int *listToArray(List *list, int n) {
    List *current = list;
    int *array = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = current -> key;
        current = current -> next;
    }
    return array;
}

void clearList(List *list) {
    if (list->next != NULL)
        clearList(list->next);
    free(list);
}

void pocketSortNoArray(int *array, int n) {
    int *copy = copy_array(array, n);

    for (int i = 0; i < n; i++) {
        while (copy[i] != i) {
            int temp = copy[copy[i]];
            copy[copy[i]] = copy[i];
            copy[i] = temp;
        }
    }
    show_array(copy, n);
    free(copy);
}

void pocketSortWithArray(int *array, int n) {
    int *copy = copy_array(array, n);

    int *help = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        help[copy[i]] = copy[i];
    }
    free(copy);
    copy = help;

    show_array(copy, n);
    free(copy);
}

int *create_array(int n, int num) {
    int *array = NULL;
    int max_key = 0;
    if (n == 1) {
        array = (int*)malloc(num * sizeof(int));
        for (int i = 0; i < num; i++)
            array[i] = i;
        int max_key = num;
    }
    else if (n == 2) {
        array = (int*)malloc(num * sizeof(int));
        int max_key = num - num / 3;
        for (int i = 0; i < max_key; i++)
            array[i] = i;
        for (int i = max_key; i < num; i++)
            array[i] = rand() % max_key;
    }
    int temp, r;
    for (int i = 0; i < num; i++) {
        r = rand() % num;
        temp = array[i];
        array[i] = array[r];
        array[r] = temp;
    }
    show_array(array, num);
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
        printf("1 - Простейшая карманная сортировка\n");
        printf("2 - Обобщенная карманная сортировка\n");
        printf("3 - Поразрядная сортировка\n");
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
            int p = 0;
            printf("Введите количество элементов массива\n");
            scanf("%d", &n);
            *array = create_array(1, n);
            printf("1 - Использовать второй массив\n");
            printf("2 - Не использовать второй массив\n");
            scanf("%d", &p);
            if (p == 1) pocketSortWithArray(*array, n);
            else if (p == 2) pocketSortNoArray(*array, n);
            else printf("Неизвестная операция.\n");
        }
        else if (result == 2) {
            printf("Введите количество элементов массива\n");
            scanf("%d", &n);
            *array = create_array(2, n);
            generalPocketSort(*array, n);
        }
        else if (result == 3) {
            printf("Введите количество элементов массива\n");
            scanf("%d", &n);
            *array = create_array(2, n);
            radixSort(*array, n);
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
