#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct StackNode {
    int level;
    Node *node;
    struct StackNode *next;
} StackNode;

Node *addNode(Node *current, int n) {
    Node *tmp;
    int left, right;
    if (n == 0) return NULL;
    else {
        left = n / 2;
        right = n - left - 1;
        tmp = (Node*)malloc(sizeof(Node));
        tmp -> data = rand() % 100;
        tmp -> left = addNode(tmp -> left, left);
        tmp -> right = addNode(tmp -> right, right);
        current = tmp;
        return tmp;
    }
}

void preOrder(Node* node, int level) {
    if (node != NULL) {
        for (int i = 0; i < level * 5; i++)
            printf(" ");
        printf("%d\n", node->data);
        preOrder(node->left, level + 1);
        preOrder(node->right, level + 1);
    }
}

void inOrder(Node* node, int level) {
    if (node != NULL) {
        inOrder(node->left, level + 1);
        for (int i = 0; i < level * 5; i++)
            printf(" ");
        printf("%d\n", node->data);
        inOrder(node->right, level + 1);
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

void inOrderNonRecursive(Node* root) {
    if (root == NULL)
        return;

    StackNode* stack = NULL;
    Node* current = root;
    int level = -1;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            level++;
            StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
            newStackNode->node = current;
            newStackNode->level = level;
            newStackNode->next = stack;
            stack = newStackNode;
            current = current->left;
        }

        if (stack != NULL) {
            StackNode* temp = stack;
            current = temp->node;
            level = temp->level;
            stack = temp->next;

            for (int i = 0; i < level * 5; i++)
                printf(" ");
            printf("%d\n", current->data);

            current = current->right;
            free(temp);
        }
    }
}

void destroyTree(Node* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        free(node);
    }
}

int main() {
    system("clear");
    
    int numNodes;
    printf("Введите количество вершин для построения: ");
    scanf("%d", &numNodes);

    Node* root = addNode(root, numNodes);

    printf("\nПрямой вывод:\n");
    preOrder(root, 0);

    printf("\nСимметричный вывод (рекурсия):\n");
    inOrder(root, 0);

    printf("\nСимметричный вывод (итерации):\n");
    inOrderNonRecursive(root);

    destroyTree(root);
    root = NULL;


    return 0;
}