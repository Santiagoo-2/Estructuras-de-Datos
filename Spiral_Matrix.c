#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;

    /* --- Lectura de dimensiones --- */
    if (printf("Ingrese N (filas) y M (columnas): "),
        scanf("%d %d", &N, &M) != 2 || N <= 0 || M <= 0) {
        fprintf(stderr, "Entrada invalida. N y M deben ser positivos.\n");
        return 1;
    }

    /* --- Reserva dinámica de matriz N x M --- */
    int **A = (int **)malloc(N * sizeof(int *));
    if (!A) { perror("malloc"); return 1; }
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(M * sizeof(int));
        if (!A[i]) { perror("malloc"); return 1; }
    }

    /* --- Lectura de elementos --- */
    printf("Ingrese los %d elementos de la matriz, fila por fila:\n", N * M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (scanf("%d", &A[i][j]) != 1) {
                fprintf(stderr, "Entrada invalida en A[%d][%d].\n", i, j);
                return 1;
            }

    /* --- Límites de la “capa” actual --- */
    int top = 0;          // primera fila no impresa aún
    int bottom = N - 1;   // última fila no impresa aún
    int left = 0;         // primera columna no impresa aún
    int right = M - 1;    // última columna no impresa aún

    /* --- Impresión en orden espiral --- */
    printf("Salida (espiral): ");
    int printed = 0, total = N * M;

    while (printed < total) {
        /* 1) Moverse izquierda->derecha por la fila 'top' */
        for (int j = left; j <= right && printed < total; j++) {
            printf("%d", A[top][j]);
            printed++;
            if (printed < total) printf(" ");
        }
        top++;  // esa fila ya quedó

        /* 2) Moverse arriba->abajo por la columna 'right' */
        for (int i = top; i <= bottom && printed < total; i++) {
            printf("%d", A[i][right]);
            printed++;
            if (printed < total) printf(" ");
        }
        right--;  // esa columna ya quedó

        /* 3) Moverse derecha->izquierda por la fila 'bottom' */
        for (int j = right; j >= left && printed < total; j--) {
            printf("%d", A[bottom][j]);
            printed++;
            if (printed < total) printf(" ");
        }
        bottom--;  // esa fila ya quedó

        /* 4) Moverse abajo->arriba por la columna 'left' */
        for (int i = bottom; i >= top && printed < total; i--) {
            printf("%d", A[i][left]);
            printed++;
            if (printed < total) printf(" ");
        }
        left++;  // esa columna ya quedó
    }
    printf("\n");

    /* --- Liberar memoria --- */
    for (int i = 0; i < N; i++) free(A[i]);
    free(A);

    return 0;
}
