#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node {
    int value;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

Node *root = NULL;
Node *parent = NULL;

Node *FindNode (int value) {
    Node *current = root;
    bool stop = false;
    while ((current != NULL) && (!stop)) {
        if (value < current->value) {
            parent = current;
            current = current -> left;
        }
        else if (value > current->value) {
            parent = current;
            current = current->right;
        }
        else stop = true;
    }
    
    return current;
}

void printBranches(int level) {
    for (int i = 0; i < level; i++) {
        if (i == level - 1) {
            printf("|--");
        } else {
            printf("|  ");
        }
    }
}

void postOrder(Node* node, int level) {
    if (node != NULL) {
        postOrder(node->right, level + 1);
        printBranches(level);
        printf("%d\n", node->value);
        postOrder(node->left, level + 1);
    }
}

void InlineShow(Node *current) {
    if (current != NULL) {
        InlineShow(current -> left);
        printf("%d (%d)\t", current->value, current->count);
        InlineShow(current -> right);
    }
}

void FindMenu() {
    int value;
    printf("Введите значение, которое хотите найти - ");
    scanf("%d", &value);
    Node *result = FindNode(value);
    if (result != NULL) {
        printf("Значение %d было найдено %d раз(-а)", value, result->count);
    }
    else printf("Значение %d не найдено", value);
}

void ShowTree(int choice) {
    if (root != NULL) {
        switch (choice)
        {
        case 1:
            printf("Вывод всех значений в строку\n");
            InlineShow(root);
            break;
        
        case 2:
            printf("Вывод в обратно-симметричном порядке\n");
            postOrder(root, 0);
            break;

        default:
            break;
        }
    }
    else printf("Дерево пустое");   
}

Node *AddRecursive(Node *current, int value) {
    if (current == NULL) {
        current = (Node*)(malloc(sizeof(Node)));
        current -> value = value;
        current -> left = current -> right = NULL;
        current -> count = 1;
    }
    else {
        if (value < current -> value)
            current -> left = AddRecursive(current -> left, value);
        else if (value > current -> value)
            current -> right = AddRecursive(current -> right, value);
        else
            current -> count++;
    }
    return current;
}

void AddNonRecursive(int value) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root -> left = root -> right = NULL;
        root -> value = value;
        root -> count = 1;
        return;
    }

    Node *parent = NULL; 
    Node *current = root;
    
    while (current != NULL) {
        parent = current;
        if (value < current -> value)
            current = current -> left;
        else if (value > current -> value)
            current = current -> right;
        else {
            current -> count++;
            return;
        }
    }

    current = (Node*)malloc(sizeof(Node));
    current -> left = current -> right = NULL;
    current -> count = 1;
    current -> value = value;

    if (value < parent -> value)
        parent -> left = current;
    else
        parent -> right = current;
}


void AddMenu() {
    int value, n;
    printf("Введите значение новой вершины - ");
    scanf("%d", &value);
    printf("\nВвыберите способ добавления. 1 - Рекурсивный, 2 - Итерационный.\n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        printf("Выбран рекурсивный способ.");
        root = AddRecursive(root, value);
        break;
    
    case 2:
        printf("Выбран итерационный способ.");
        AddNonRecursive(value);
        break;

    default:
        printf("Выбрана неизвестная операция.");
        break;
    }
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        printf("Вершина не найдена");
        return root;
    }

    if (key < root->value) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->value) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            printf("Вершина удалена");
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            printf("Вершина удалена");
            return temp;
        }

        Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

void createTree() {
    srand(time(NULL));
    int num;
    printf("Введите количество вершин для построения: ");
    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        root = AddRecursive(root, rand() % 100);
    }
    
}

void ShowMenu() {
    int choice;
    printf("Выберите способ вывода. 1 - В одну строку. 2 - Обратно-симметричный обход - ");
    scanf("%d", &choice);
    if (choice == 1){
        ShowTree(1);
    }
    else if (choice == 2){
        ShowTree(2);
    }
    else printf("Неизвестная операция. Повторите попытку");
}

void DeleteMenu() {
    int value;
    ShowTree(2);
    printf("\nВведите значение для удаления - ");
    scanf("%d", &value);
    root = deleteNode(root, value);   
}

void destroyTree(Node* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        free(node);
    }
}

void mainMenu() {

    while (1) {
        int choice, value;
        system("clear");
        printf("1. Создать дерево\n");
        printf("2. Добавить вершину\n");
        printf("3. Поиск вершины\n");
        printf("4. Вывести состояние дерева\n");
        printf("5. Удалить вершину\n");
        printf("6. Очистить дерево\n");
        printf("0. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createTree();
                printf("\nДерево cоздано");
                break;
            case 2:
                AddMenu();
                break;
            case 3:
                FindMenu();
                break;
            case 4:
                ShowMenu();
                break;
            case 5:
                DeleteMenu();
                break;
            case 6:
                destroyTree(root);
                root = NULL;
                printf("\nДерево очищено");
                break;
            case 0:
                destroyTree(root);
                root = NULL;
                exit(0);
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        getchar();
        getchar();
    }
}

int main() {
    srand(time(NULL));
    mainMenu();
    return EXIT_SUCCESS;
}