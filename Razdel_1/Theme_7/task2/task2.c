#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Stack {
    int data;
    struct Stack* next;
} Stack;

typedef struct Queue {
    int value;
    struct Queue* next;
} Queue;

void push(Stack** top, int data) {
    Stack* new_node = (Stack*)malloc(sizeof(Stack));
    if (new_node == NULL) {
        printf("Ошибка: недостаточно памяти для создания нового элемента стека\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(Stack** top) {
    if (*top == NULL) {
        printf("Стек пуст\n");
        exit(1);
    }
    int data = (*top)->data;
    Stack* temp = *top;
    *top = (*top)->next;
    free(temp);
    return data;
}

bool is_empty_stack(Stack* top) {
    return top == NULL;
}

void enqueue(Queue** front, Queue** rear, int value) {
    Queue* new_node = (Queue*)malloc(sizeof(Queue));
    if (new_node == NULL) {
        printf("Ошибка: недостаточно памяти для создания нового элемента очереди\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = NULL;
    if (*rear == NULL) {
        *front = new_node;
    } else {
        (*rear)->next = new_node;
    }
    *rear = new_node;
}

int dequeue(Queue** front, Queue** rear) {
    if (*front == NULL) {
        printf("Очередь пуста\n");
        exit(1);
    }
    int value = (*front)->value;
    Queue* temp = *front;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    free(temp);
    return value;
}

bool is_empty_queue(Queue* front) {
    return front == NULL;
}

void matrix_to_list(int matrix[][MAX_VERTICES], int vertices, Node* adjacency_list[]) {
    for (int i = 0; i < vertices; i++) {
        adjacency_list[i] = NULL;
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                Node* new_node = (Node*)malloc(sizeof(Node));
                new_node->vertex = j;
                new_node->next = adjacency_list[i];
                adjacency_list[i] = new_node;
            }
        }
    }
}

void list_to_matrix(Node* adjacency_list[], int vertices, int matrix[][MAX_VERTICES]) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
        }
    }
    
    for (int i = 0; i < vertices; i++) {
        Node* current = adjacency_list[i];
        while (current != NULL) {
            matrix[i][current->vertex] = 1;
            current = current->next;
        }
    }
}

void add_edge(int matrix[][MAX_VERTICES], Node* adjacency_list[], int vertex1, int vertex2) {
    matrix[vertex1][vertex2] = 1;
    matrix[vertex2][vertex1] = 1;
}

void remove_edge(Node* adjacency_list[], int matrix[][MAX_VERTICES], int vertex1, int vertex2) {
    matrix[vertex1][vertex2] = 0;
    matrix[vertex2][vertex1] = 0;
}



void add_vertex(Node* adjacency_list[], int vertex) {
    adjacency_list[vertex] = NULL;
}

void remove_vertex(Node* adjacency_list[], int vertex, int vertices) {
    for (int i = 0; i < vertices; i++) {
        Node* current = adjacency_list[i];
        Node* prev = NULL;
        while (current != NULL) {
            if (current->vertex == vertex) {
                if (prev == NULL) {
                    adjacency_list[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }
    adjacency_list[vertex] = NULL;
}

void dfs(int start_vertex, int vertices, int matrix[][MAX_VERTICES]) {
    bool visited[MAX_VERTICES] = {false};
    Stack* stack = NULL;
    
    printf("Обход графа в глубину: ");
    
    push(&stack, start_vertex);
    visited[start_vertex] = true;
    
    while (!is_empty_stack(stack)) {
        int vertex = pop(&stack);
        printf("%d ", vertex);
        
        for (int i = 0; i < vertices; i++) {
            if (matrix[vertex][i] && !visited[i]) {
                push(&stack, i);
                visited[i] = true;
            }
        }
    }
    printf("\n");
}

void bfs(int start_vertex, int vertices, int matrix[][MAX_VERTICES]) {
    bool visited[MAX_VERTICES] = {false};
    Queue* front = NULL;
    Queue* rear = NULL;
    
    printf("Обход графа в ширину: ");
    
    enqueue(&front, &rear, start_vertex);
    visited[start_vertex] = true;
    
    while (!is_empty_queue(front)) {
        int vertex = dequeue(&front, &rear);
        printf("%d ", vertex);
        
        for (int i = 0; i < vertices; i++) {
            if (matrix[vertex][i] && !visited[i]) {
                enqueue(&front, &rear, i);
                visited[i] = true;
            }
        }
    }
    printf("\n");
}

void print_matrix(int matrix[][MAX_VERTICES], int vertices) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_adjacency_list(Node* adjacency_list[], int vertices) {
    printf("Список смежности:\n");
    for (int i = 0; i < vertices; i++) {
        printf("Вершина %d: ", i);
        Node* current = adjacency_list[i];
        while (current != NULL) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

void free_memory(Node* adjacency_list[], int vertices) {

    for (int i = 0; i < vertices; i++) {
        Node* current = adjacency_list[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        adjacency_list[i] = NULL;
    }
}

int main() {
    int vertices, edges, choice, vertex1, vertex2, start_vertex;
    Node* adjacency_list[MAX_VERTICES];
    int matrix[MAX_VERTICES][MAX_VERTICES] = {0};
    
    printf("Введите количество вершин: ");
    scanf("%d", &vertices);
    
    printf("Введите количество рёбер: ");
    scanf("%d", &edges);
    
    printf("Введите рёбра (номера вершин):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &vertex1, &vertex2);
        add_edge(matrix, adjacency_list, vertex1, vertex2);
    }
    
    matrix_to_list(matrix, vertices, adjacency_list);
    
    do {
        printf("\nВыберите операцию:\n");
        printf("1. Печать матрицы смежности\n");
        printf("2. Печать списка смежности\n");
        printf("3. Обход графа в глубину\n");
        printf("4. Обход графа в ширину\n");
        printf("5. Добавление нового ребра\n");
        printf("6. Удаление заданного ребра\n");
        printf("7. Добавление новой вершины\n");
        printf("8. Удаление заданной вершины\n");
        printf("9. Преобразовать матрицу смежности в список смежности\n");
        printf("10. Преобразовать список смежности в матрицу смежности\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                print_matrix(matrix, vertices);
                break;
            case 2:
                matrix_to_list(matrix, vertices, adjacency_list);
                print_adjacency_list(adjacency_list, vertices);
                break;
            case 3:
                printf("Введите начальную вершину для обхода в глубину: ");
                scanf("%d", &start_vertex);
                dfs(start_vertex, vertices, matrix);
                break;
            case 4:
                printf("Введите начальную вершину для обхода в ширину: ");
                scanf("%d", &start_vertex);
                bfs(start_vertex, vertices, matrix);
                break;
            case 5:
                printf("Введите ребро для добавления (номера вершин): ");
                scanf("%d %d", &vertex1, &vertex2);
                add_edge(matrix, adjacency_list, vertex1, vertex2);
                break;
            case 6:
                printf("Введите ребро для удаления (номера вершин): ");
                scanf("%d %d", &vertex1, &vertex2);
                remove_edge(adjacency_list, matrix, vertex1, vertex2);
                break;
            case 7:
                vertices++;
                add_vertex(adjacency_list, vertices - 1);
                break;
            case 8:
                printf("Введите вершину для удаления: ");
                scanf("%d", &vertex1);
                if (vertex1 < vertices && vertex1 >= 0) {
                    vertices--;
                    remove_vertex(adjacency_list, vertex1, vertices);
                } else {
                    printf("Неверный номер вершины.\n");
                }
                break;
            case 9:
                matrix_to_list(matrix, vertices, adjacency_list);
                printf("Матрица смежности успешно преобразована в список смежности.\n");
                break;
            case 10:
                list_to_matrix(adjacency_list, vertices, matrix);
                printf("Список смежности успешно преобразован в матрицу смежности.\n");
                break;
            case 0:
                free_memory(adjacency_list, vertices);
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
            }
    } while(choice != 0);


    return 0;

}

