#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;
    int **A, **B, **C;

    // --- Pedir dimensiones ---
    printf("Ingrese el numero de filas: ");
    scanf("%d", &rows);
    printf("Ingrese el numero de columnas: ");
    scanf("%d", &cols);

    // --- Reserva dinamica de A, B y C ---
    A = (int **)malloc(rows * sizeof(int *));
    B = (int **)malloc(rows * sizeof(int *));
    C = (int **)malloc(rows * sizeof(int *));
    
// Este ciclo for recorre cada fila y reserva espacio para 'cols' enteros en cada una.
    for (int i = 0; i < rows; i++) {
        A[i] = (int *)malloc(cols * sizeof(int));// Reserva memoria para la fila i de A.
        B[i] = (int *)malloc(cols * sizeof(int));// Reserva memoria para la fila i de B.
        C[i] = (int *)malloc(cols * sizeof(int));// Reserva memoria para la fila i de C.
        
    }

    // --- Llenar matriz A ---
    printf("Ingrese los elementos de la matriz A (%d valores):\n", rows * cols);
    // Este doble for recorre todas las posiciones de la matriz A.
    for (int i = 0; i < rows; i++) { // Recorre cada fila.
        for (int j = 0; j < cols; j++) { // Recorre cada columna.
            scanf("%d", (*(A + i) + j));  // equivalente a &A[i][j]
        }
    }

    // --- Llenar matriz B ---
    printf("Ingrese los elementos de la matriz B (%d valores):\n", rows * cols);
    // Otro doble for que recorre todas las posiciones de la matriz B.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", (*(B + i) + j));  // equivalente a &B[i][j]
        }
    }

    // --- Sumar matrices: C = A + B -
     // Este doble for recorre cada posición y suma los elementos correspondientes.--
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(C + i) + j) = *(*(A + i) + j) + *(*(B + i) + j);
            // equivale a C[i][j] = A[i][j] + B[i][j]
        }
    }

    // --- Imprimir matriz resultado ---
    printf("\nMatriz C = A + B:\n");
    // Doble for para imprimir todos los elementos de la matriz C.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(*(C + i) + j));
        }
        printf("\n");
    }

    // --- Liberar memoria ---
    for (int i = 0; i < rows; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
