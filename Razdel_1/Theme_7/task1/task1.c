#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODES 100

typedef struct Node {
    int data;
    int parent_index;
    struct Node* next_sibling;
} Node;

typedef struct Tree {
    Node* nodes[MAX_NODES];
    int size;
} Tree;

void initTree(Tree* tree, int root_data) {
    tree->size = 0;
    tree->nodes[0] = (Node*)malloc(sizeof(Node));
    if (tree->nodes[0] == NULL) {
        printf("Ошибка: невозможно выделить память для корневой вершины.\n");
        exit(EXIT_FAILURE);
    }
    tree->nodes[0]->data = root_data;
    tree->nodes[0]->parent_index = -1;
    tree->nodes[0]->next_sibling = NULL;
    tree->size++;
}


void addChild(Tree* tree, int parent_data, int data) {
    int parent_index = -1;
    for (int i = 0; i < tree->size; i++) {
        if (tree->nodes[i] != NULL && tree->nodes[i]->data == parent_data) {
            parent_index = i;
            break;
        }
    }
    
    if (parent_index == -1) {
        printf("Ошибка: вершина со значением %d не найдена.\n", parent_data);
        return;
    }
    
    if (tree->size >= MAX_NODES) {
        printf("Ошибка: превышен максимальный размер дерева.\n");
        return;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка: невозможно выделить память для нового узла.\n");
        return;
    }
    
    new_node->data = data;
    new_node->parent_index = parent_index;
    new_node->next_sibling = NULL;
    
    if (parent_index == -1) {
        tree->nodes[tree->size++] = new_node;
        return;
    }

    if (tree->nodes[parent_index] == NULL) {
        tree->nodes[parent_index] = new_node;
    } else {
        Node* current = tree->nodes[parent_index];
        while (current->next_sibling != NULL) {
            current = current->next_sibling;
        }
        current->next_sibling = new_node;
    }
    
    tree->nodes[tree->size++] = new_node;
    printf("Вершина со значением %d добавлена как потомок вершины со значением %d.\n", data, parent_data);
}



void printTree(Tree* tree) {
    printf("Вершины дерева:\n");
    for (int i = 0; i < tree->size; i++) {
        Node* node = tree->nodes[i];
        if (node != NULL) {
            if (node->parent_index == -1) {
                printf("Вершина %d (Корень)\n", node->data);
            } else {
                printf("Вершина %d (Родитель %d)\n", node->data, tree->nodes[node->parent_index]->data);
            }
        }
    }
}


int findNode(Tree* tree, int data) {
    for (int i = 0; i < tree->size; i++) {
        Node* node = tree->nodes[i];
        if (node != NULL && node->data == data) {
            return i;
        }
    }
    return -1;
}

void removeNode(Tree* tree, int data) {
    int index = findNode(tree, data);
    if (index != -1) {
        Node* node_to_remove = tree->nodes[index];
        
        if (node_to_remove->parent_index != -1) {
            Node* parent = tree->nodes[node_to_remove->parent_index];
            if (parent != NULL) {
                if (parent->next_sibling == node_to_remove) {
                    parent->next_sibling = node_to_remove->next_sibling;
                }
            }
        }
        
        while (node_to_remove != NULL) {
            Node* next_sibling = node_to_remove->next_sibling;
            free(node_to_remove);
            node_to_remove = next_sibling;
        }
        
        tree->nodes[index] = NULL;
        printf("Вершина со значением %d успешно удалена.\n", data);
    } else {
        printf("Ошибка: вершина со значением %d не найдена.\n", data);
    }
    tree->size--;
}


void clearTree(Tree* tree) {
    for (int i = 0; i < tree->size; i++) {
        free(tree->nodes[i]);
    }
    tree->size = 0;
}

int main() {

    srand(time(NULL));

    Tree tree;
    int choice;
    int parent_data, data, search_data, num_elements;
    int search_result;
    
    do {
        printf("\nВыберите действие:\n");
        printf("1. Добавить вершину\n");
        printf("2. Удалить вершину\n");
        printf("3. Найти вершину\n");
        printf("4. Вывести дерево\n");
        printf("0. Выйти\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (tree.size == 0) {
                    printf("Дерево пустое. Введите значение корня: ");
                    scanf("%d", &parent_data);
                    initTree(&tree, parent_data);
                } else {
                    printf("Введите значение родителя: ");
                    scanf("%d", &parent_data);
                    printf("Введите значение новой вершины: ");
                    scanf("%d", &data);
                    addChild(&tree, parent_data, data);
                }
                break;
            case 2:
                printf("Введите значение вершины для удаления: ");
                scanf("%d", &data);
                removeNode(&tree, data);
                break;
            case 3:
                printf("Введите значние вершины для поиска: ");
                scanf("%d", &search_data);
                search_result = findNode(&tree, search_data);
                if (search_result != -1) {
                    printf("Вершина найдена на позиции %d\n", search_result);
                } else {
                    printf("Вершина не найдена\n");
                }
                break;
            case 4:
                printTree(&tree);
                break;
            case 0:
                clearTree(&tree);
                printf("Выход из программы.\n");
                break;
            default:
                printf("Ошибка: неверный выбор. Попробуйте снова.\n");
                break;
        }
    } while (choice != 0);
    
    return 0;
}
