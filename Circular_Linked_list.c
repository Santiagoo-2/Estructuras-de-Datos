#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// =========================================================
// 1. ESTRUCTURAS DEL TDA
// =========================================================

// Estructura del Nodo de la lista
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Estructura principal del TDA Lista Enlazada Circular
typedef struct CircularLinkedList {
    Node *tail; // Puntero al último nodo
    int size;   // Contador para saber el tamaño de la lista
} CircularLinkedList;


// =========================================================
// 2. PROTOTIPOS DE FUNCIONES DEL TDA
// =========================================================

// Inicialización
CircularLinkedList* createList();

// Funciones de ADT
void AddToFront(CircularLinkedList *list, int data);
void AddToEnd(CircularLinkedList *list, int data);
void AddAtPosition(CircularLinkedList *list, int data, int position);
int RemoveFromFront(CircularLinkedList *list);
int RemoveFromEnd(CircularLinkedList *list);
int RemoveFromPosition(CircularLinkedList *list, int position);
bool Search(CircularLinkedList *list, int key);
void Traverse(CircularLinkedList *list); 
int Size(CircularLinkedList *list);
bool IsEmpty(CircularLinkedList *list);
void Clear(CircularLinkedList *list);
void Display(CircularLinkedList *list);
Node* GetHead(CircularLinkedList *list);
Node* GetTail(CircularLinkedList *list);

// Función Auxiliar
Node* createNewNode(int data);


// =========================================================
// 3. IMPLEMENTACIÓN DE FUNCIONES DEL TDA
// =========================================================

/**
 * @brief Crea un nuevo nodo.
 */
Node* createNewNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Error de asignación de memoria para el nodo");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Inicializa una nueva lista circular vacía.
 */
CircularLinkedList* createList() {
    CircularLinkedList *list = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    if (list == NULL) {
        perror("Error de asignación de memoria para la lista");
        exit(EXIT_FAILURE);
    }
    list->tail = NULL;
    list->size = 0;
    return list;
}

// ---------------------------------------------------------
// FUNCIONES DE INFORMACIÓN
// ---------------------------------------------------------

/**
 * @brief Verifica si la lista está vacía.
 */
bool IsEmpty(CircularLinkedList *list) {
    return list->tail == NULL;
}

/**
 * @brief Retorna el número de elementos en la lista.
 */
int Size(CircularLinkedList *list) {
    return list->size;
}

/**
 * @brief Retorna el puntero al nodo cabeza (head).
 */
Node* GetHead(CircularLinkedList *list) {
    return IsEmpty(list) ? NULL : list->tail->next;
}

/**
 * @brief Retorna el puntero al nodo cola (tail).
 */
Node* GetTail(CircularLinkedList *list) {
    return list->tail;
}

// ---------------------------------------------------------
// FUNCIONES ADD (INSERTAR)
// ---------------------------------------------------------

/**
 * @brief Inserta un nuevo nodo al inicio (cabeza) de la lista.
 */
void AddToFront(CircularLinkedList *list, int data) {
    Node *newNode = createNewNode(data);

    if (IsEmpty(list)) {
        list->tail = newNode;
        newNode->next = newNode; // Apunta a sí mismo
    } else {
        newNode->next = list->tail->next; // Nuevo nodo apunta a la cabeza actual
        list->tail->next = newNode;        // El último nodo apunta al nuevo nodo (nueva cabeza)
    }
    list->size++;
}

/**
 * @brief Inserta un nuevo nodo al final (cola) de la lista.
 */
void AddToEnd(CircularLinkedList *list, int data) {
    // La inserción al final es casi idéntica a AddToFront,
    // solo se necesita actualizar 'tail' al final.
    AddToFront(list, data); 
    if (list->size > 1) { 
        list->tail = list->tail->next; // El nuevo nodo es ahora el último
    }
}

/**
 * @brief Inserta un nuevo nodo en una posición específica.
 */
void AddAtPosition(CircularLinkedList *list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("ERROR: Posición %d inválida. Debe estar entre 0 y %d.\n", position, list->size);
        return;
    }

    if (position == 0) {
        AddToFront(list, data);
    } else if (position == list->size) {
        AddToEnd(list, data);
    } else {
        Node *newNode = createNewNode(data);
        Node *current = list->tail->next; // Inicia en la cabeza

        // Mover 'current' a la posición (position - 1)
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        // Inserción
        newNode->next = current->next;
        current->next = newNode;
        list->size++;
    }
}

// ---------------------------------------------------------
// FUNCIONES REMOVE (ELIMINAR)
// ---------------------------------------------------------

/**
 * @brief Elimina el nodo del frente (cabeza) de la lista.
 */
int RemoveFromFront(CircularLinkedList *list) {
    if (IsEmpty(list)) {
        printf("ERROR: La lista está vacía.\n");
        return -1; // Valor de error
    }

    Node *nodeToDelete = list->tail->next; // El nodo cabeza
    int data = nodeToDelete->data;

    if (list->size == 1) {
        list->tail = NULL; // La lista queda vacía
    } else {
        list->tail->next = nodeToDelete->next; // El último apunta a la nueva cabeza
    }

    free(nodeToDelete);
    list->size--;
    return data;
}

/**
 * @brief Elimina el nodo del final (cola) de la lista.
 */
int RemoveFromEnd(CircularLinkedList *list) {
    if (IsEmpty(list)) {
        printf("ERROR: La lista está vacía.\n");
        return -1; // Valor de error
    }

    if (list->size == 1) {
        return RemoveFromFront(list);
    }

    Node *current = list->tail->next; // La cabeza
    // Mover 'current' hasta el nodo *antes* del último
    while (current->next != list->tail) {
        current = current->next;
    }

    Node *nodeToDelete = list->tail;
    int data = nodeToDelete->data;

    current->next = list->tail->next; // El nuevo último apunta a la cabeza
    list->tail = current;             // El penúltimo es ahora la nueva cola

    free(nodeToDelete);
    list->size--;
    return data;
}

/**
 * @brief Elimina un nodo en una posición específica.
 */
int RemoveFromPosition(CircularLinkedList *list, int position) {
    if (IsEmpty(list)) {
        printf("ERROR: La lista está vacía.\n");
        return -1;
    }
    if (position < 0 || position >= list->size) {
        printf("ERROR: Posición %d inválida. Debe estar entre 0 y %d.\n", position, list->size - 1);
        return -1;
    }

    if (position == 0) {
        return RemoveFromFront(list);
    }
    if (position == list->size - 1) {
        return RemoveFromEnd(list);
    }

    Node *prev = list->tail->next; // La cabeza
    // Mover 'prev' a la posición (position - 1)
    for (int i = 0; i < position - 1; i++) {
        prev = prev->next;
    }

    Node *nodeToDelete = prev->next;
    int data = nodeToDelete->data;

    prev->next = nodeToDelete->next; // Salta el nodo a eliminar

    free(nodeToDelete);
    list->size--;
    return data;
}

// ---------------------------------------------------------
// FUNCIONES DE UTILIDAD
// ---------------------------------------------------------

/**
 * @brief Busca un elemento en la lista.
 */
bool Search(CircularLinkedList *list, int key) {
    if (IsEmpty(list)) {
        return false;
    }

    Node *current = list->tail->next; // Comienza en la cabeza
    
    // Usamos un do-while para garantizar que el bucle se ejecute al menos una vez
    do {
        if (current->data == key) {
            return true;
        }
        current = current->next;
    } while (current != list->tail->next); // Se detiene al regresar a la cabeza

    return false;
}

/**
 * @brief Muestra el contenido de la lista.
 */
void Display(CircularLinkedList *list) {
    if (IsEmpty(list)) {
        printf("Lista: VACÍA\n");
        return;
    }

    Node *current = list->tail->next; // Comienza en la cabeza

    printf("Lista Circular (Tamaño: %d): ", list->size);
    do {
        printf("%d", current->data);
        current = current->next;
        if (current != list->tail->next) {
            printf(" -> ");
        }
    } while (current != list->tail->next); 
    
    printf(" -> (HEAD)\n");
}

/**
 * @brief Alias para Display.
 */
void Traverse(CircularLinkedList *list) {
    Display(list); 
}

/**
 * @brief Libera la memoria de todos los nodos y reinicia la lista.
 */
void Clear(CircularLinkedList *list) {
    if (IsEmpty(list)) return;

    Node *current = list->tail->next;
    Node *next = NULL;

    // Recorre y libera hasta que la cabeza sea liberada
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != list->tail->next); // El bucle se rompe al volver a la cabeza (que ya se liberó)

    // El último nodo (tail) también apunta a la cabeza que fue liberada, por eso se rompe el ciclo.
    list->tail = NULL;
    list->size = 0;
}


// =========================================================
// 4. FUNCIÓN PRINCIPAL (MAIN) PARA PRUEBAS Y LECTURA DE DATOS
// =========================================================

int main() {
    CircularLinkedList *myList = createList();
    int choice, data, position;
    int result;

    printf("--- TDA Lista Enlazada Circular en C ---\n");
    
    // --- Pruebas Iniciales ---
    AddToEnd(myList, 10);
    AddToEnd(myList, 20);
    AddToFront(myList, 5);
    AddAtPosition(myList, 15, 2); 
    printf("Lista inicial:\n");
    Display(myList); // Resultado esperado: 5 -> 10 -> 15 -> 20 -> (HEAD)
    printf("Cabeza: %d, Cola: %d\n", GetHead(myList)->data, GetTail(myList)->data);
    printf("----------------------------------------\n");

    // --- Bucle de Menú para Leer Datos del Teclado y Testear ---
    do {
        printf("\nMENU DE OPERACIONES:\n");
        printf(" 1. Agregar al frente\n");
        printf(" 2. Agregar al final\n");
        printf(" 3. Agregar en posición\n");
        printf(" 4. Eliminar del frente\n");
        printf(" 5. Eliminar del final\n");
        printf(" 6. Eliminar de posición\n");
        printf(" 7. Buscar elemento\n");
        printf(" 8. Mostrar lista (Traverse/Display)\n");
        printf(" 9. Mostrar tamaño (Size) / Es vacía (IsEmpty)\n");
        printf("10. Limpiar lista (Clear)\n");
        printf("11. Salir\n");
        printf("Selecciona una opción: ");
        
        // Manejo simple de entrada
        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Saliendo...\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Dato a insertar al frente: ");
                scanf("%d", &data);
                AddToFront(myList, data);
                break;
            case 2:
                printf("Dato a insertar al final: ");
                scanf("%d", &data);
                AddToEnd(myList, data);
                break;
            case 3:
                printf("Dato a insertar: ");
                scanf("%d", &data);
                printf("Posición (0 a %d): ", Size(myList));
                scanf("%d", &position);
                AddAtPosition(myList, data, position);
                break;
            case 4:
                result = RemoveFromFront(myList);
                if (result != -1) printf("Elemento eliminado del frente: %d\n", result);
                break;
            case 5:
                result = RemoveFromEnd(myList);
                if (result != -1) printf("Elemento eliminado del final: %d\n", result);
                break;
            case 6:
                printf("Posición a eliminar (0 a %d): ", Size(myList) - 1);
                scanf("%d", &position);
                result = RemoveFromPosition(myList, position);
                if (result != -1) printf("Elemento eliminado de la posición %d: %d\n", position, result);
                break;
            case 7:
                printf("Elemento a buscar: ");
                scanf("%d", &data);
                if (Search(myList, data)) {
                    printf(" El elemento %d fue encontrado.\n", data);
                } else {
                    printf(" El elemento %d NO fue encontrado.\n", data);
                }
                break;
            case 8:
                Traverse(myList);
                break;
            case 9:
                printf("Tamaño de la lista: %d\n", Size(myList));
                printf("¿Lista vacía?: %s\n", IsEmpty(myList) ? "Sí" : "No");
                break;
            case 10:
                Clear(myList);
                printf("Lista limpiada y memoria liberada.\n");
                break;
            case 11:
                printf("Saliendo del programa. La memoria será liberada.\n");
                break;
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
        
        // Muestra el estado de la lista después de cada operación (excepto 7, 9, 11)
        if (choice >= 1 && choice <= 6) {
            Display(myList);
        }

    } while (choice != 11);

    // Liberar memoria final
    Clear(myList);
    free(myList);

    return 0;
}