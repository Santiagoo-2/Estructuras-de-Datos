#include <stdio.h>
#include <stdlib.h>

// Estructura de un nodo del árbol binario
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Función para crear un nuevo nodo
struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Recorrido Pre-order: Root -> Left -> Right
void preorder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Recorrido In-order: Left -> Root -> Right
void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Recorrido Post-order: Left -> Right -> Root
void postorder(struct Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    // Crear nodos del árbol
    struct Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(12);
    root->right->right = newNode(18);

    printf("Pre-order traversal: ");
    preorder(root);

    printf("\nIn-order traversal: ");
    inorder(root);

    printf("\nPost-order traversal: ");
    postorder(root);

    printf("\n");

    return 0;
}
