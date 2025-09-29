#include <stdio.h>
#include <stdlib.h> 

typedef struct Node {
    int data;            
    struct Node *next;   
} Node;

// Estructura para gestionar la Lista Enlazada
typedef struct LinkedList {
    Node *head;
} LinkedList;

// =========================================================
// 2. IMPLEMENTACIÓN DE FUNCIONES
// =========================================================

// Función auxiliar para inicializar la lista
LinkedList* create_list() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        perror("Error al asignar memoria para la lista");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

// b. Display Nodes (Mostrar Nodos)
void display_nodes(LinkedList *list) {
    if (list->head == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// c. Insert Node at beginning (Insertar Nodo al principio)
void insert_at_beginning(LinkedList *list, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
}

// e. Insert Node at the end of Linked List (Insertar Nodo al final)
void insert_at_end(LinkedList *list, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    Node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

// d. Insert Node in specific position (Insertar Nodo en posición específica, índice 0)
void insert_at_position(LinkedList *list, int data, int position) {
    if (position < 0) {
        printf("Posición inválida.\n");
        return;
    }
    if (position == 0) {
        insert_at_beginning(list, data);
        return;
    }

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;

    Node *current = list->head;
    int count = 0;

    // Recorrer hasta la posición anterior a la deseada (position - 1)
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("La posición %d está fuera de los límites de la lista.\n", position);
        free(new_node); 
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

// f. Delete Node at beginning (Eliminar Nodo al principio)
void delete_at_beginning(LinkedList *list) {
    if (list->head == NULL) {
        printf("Lista vacía, nada que eliminar.\n");
        return;
    }

    Node *temp = list->head;     
    list->head = list->head->next;
    free(temp);                 
}

// g. Delete Node at end (Eliminar Nodo al final)
void delete_at_end(LinkedList *list) {
    if (list->head == NULL) {
        printf("Lista vacía, nada que eliminar.\n");
        return;
    }

    // Caso: solo hay un nodo
    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL;
        return;
    }

    Node *current = list->head;
    // Recorrer hasta el penúltimo nodo
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next); // Liberar el último nodo
    current->next = NULL; // El penúltimo nodo ahora es el último
}

// h. Delete Node at position (Eliminar Nodo en posición, índice 0)
void delete_at_position(LinkedList *list, int position) {
    if (list->head == NULL) {
        printf("Lista vacía, nada que eliminar.\n");
        return;
    }
    if (position < 0) {
        printf("Posición inválida.\n");
        return;
    }

    // Si se elimina la cabeza (posición 0)
    if (position == 0) {
        delete_at_beginning(list);
        return;
    }

    Node *current = list->head;
    Node *prev = NULL;
    int count = 0;

    // Recorrer hasta el nodo a eliminar (current) y guardar el anterior (prev)
    while (current != NULL && count < position) {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("La posición %d está fuera de los límites de la lista.\n", position);
        return;
    }

    // Saltar el nodo a eliminar y liberarlo
    prev->next = current->next;
    free(current);
}

// Función para liberar toda la memoria (¡importante en C!)
void destroy_list(LinkedList *list) {
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current); 
        current = next;
    }
    free(list); 
}

// =========================================================
// 3. FUNCIÓN MAIN (EJEMPLO DE USO)
// =========================================================

int main() {
    LinkedList *my_list = create_list();

    printf("--- INICIALIZACIÓN Y ADICIÓN ---\n");
    // c. Insertar al principio
    insert_at_beginning(my_list, 10);
    insert_at_beginning(my_list, 5);
    // e. Insertar al final
    insert_at_end(my_list, 20);
    insert_at_end(my_list, 30);
    
    printf("Lista inicial (5 -> 10 -> 20 -> 30):\n");
    display_nodes(my_list); // b. Mostrar

    printf("\n--- INSERCIÓN EN POSICIÓN ---\n");
    // d. Insertar en posición 2 (entre 10 y 20)
    insert_at_position(my_list, 15, 2); 
    printf("Lista despues de insertar 15 en pos 2 (5 -> 10 -> 15 -> 20 -> 30):\n");
    display_nodes(my_list);

    printf("\n--- ELIMINACIÓN ---\n");
    // f. Eliminar al principio
    delete_at_beginning(my_list);
    printf("Lista despues de eliminar al principio (10 -> 15 -> 20 -> 30):\n");
    display_nodes(my_list);

    // h. Eliminar en posición 1 (eliminar el 15)
    delete_at_position(my_list, 1);
    printf("Lista despues de eliminar en pos 1 (10 -> 20 -> 30):\n");
    display_nodes(my_list);

    // g. Eliminar al final
    delete_at_end(my_list);
    printf("Lista despues de eliminar al final (10 -> 20):\n");
    display_nodes(my_list);

    // Limpieza de memoria (¡Esencial en C!)
    destroy_list(my_list);

    return 0;
}