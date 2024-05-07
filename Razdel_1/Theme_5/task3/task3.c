#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* root;

Node* search(Node* node, int value) {
    if (node == NULL || node->data == value)
        return node;

    if (value < node->data)
        return search(node->left, value);

    else
        return search(node->right, value);
}

void addChild(Node* parent, int value, int side) {
    Node* child = (Node*)malloc(sizeof(Node));
    child->data = value;
    child->left = NULL;
    child->right = NULL;

    if (side == 0) {
        if (parent->left == NULL)
            parent->left = child;
        else {
            printf("Левый потомок уже существует.\n");
            free(child);
        }
    } else if (side == 1) {
        if (parent->right == NULL)
            parent->right = child;
        else {
            printf("Правый потомок уже существует.\n");
            free(child);
        }
    }
}

void postOrder(Node* node, int level) {
    if (node != NULL) {
        postOrder(node->right, level + 1);
        for (int i = 0; i < level * 5; i++)
            printf(" ");
        printf("%d\n", node->data);
        postOrder(node->left, level + 1);
    }
}

void destroyTree(Node* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        free(node);
    }
}

void addRoot(int value) {
    root = (Node*)malloc(sizeof(Node));
    root -> left = NULL;
    root -> right = NULL;
    root -> data = value;
    printf("Корень создан\n");
}

void mainMenu() {

    while (1) {
        int choice, value;
        system("clear");
        printf("1. Поиск вершины\n");
        printf("2. Добавление потомка\n");
        printf("3. Построчный вывод дерева\n");
        printf("4. Уничтожение дерева\n");
        printf("0. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root!=NULL) {
                    printf("Введите значение для поиска: ");
                    scanf("%d", &value);
                    if (search(root,value) != NULL)
                        printf("Вершина найдена.\n");
                    else
                        printf("Вершина не найдена.\n");
                }
                else printf("Дерево пустое.");
                break;
            case 2:
                if (root != NULL) {
                    printf("Введите значение родительской вершины: ");
                    scanf("%d", &value);
                    Node* parent = search(root, value);
                    if (parent == NULL) {
                        printf("Родительская вершина не найдена.\n");
                        break;
                    }
                    printf("Введите значение новой вершины: ");
                    scanf("%d", &value);
                    printf("Введите сторону (0 - левый, 1 - правый): ");
                    int side;
                    scanf(" %d", &side);
                    addChild(parent, value, side);
                }
                else {
                    printf("Дерево пустое. Нужно создать корень.\n");
                    printf("Введите значение корня: ");
                    scanf("%d", &value);
                    addRoot(value);                   
                }
                break;
            case 3:
                printf("\nПострочный вывод дерева:\n");
                postOrder(root, 0);
                break;
            case 4:
                destroyTree(root);
                root = NULL;
                printf("Дерево успешно уничтожено.\n");
                break;
            case 0:
                destroyTree(root);
                exit(0);
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        getchar();
        getchar();
    }
}

int main() {
    root = NULL;
    mainMenu();
    return EXIT_SUCCESS;
}