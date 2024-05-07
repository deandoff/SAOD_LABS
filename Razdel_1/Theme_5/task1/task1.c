#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

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

void destroyTree(Node* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        free(node);
    }
}

int main() {
    system("clear");

    srand(time(NULL));

    int numNodes;
    printf("Введите количество вершин для построения: ");
    scanf("%d", &numNodes);

    Node *root = addNode(root, numNodes);

    printf("\nПрямой вывод:\n");
    preOrder(root, 0);

    printf("\nСимметричный вывод:\n");
    inOrder(root, 0);

    printf("\nОбратно-симметричный вывод:\n");
    postOrder(root, 0);
    
    destroyTree(root);
    root = NULL;

    return 0;
}