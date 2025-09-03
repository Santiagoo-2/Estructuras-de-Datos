#include <stdio.h>
#include <stdlib.h>

// Función para calcular la suma total de las ventas
float totalSale(float sales[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += sales[i];
    }
    return total;
}

// Función para calcular la venta máxima
float maxSale(float sales[], int n) {
    float max = sales[0];
    for (int i = 1; i < n; i++) {
        if (sales[i] > max) {
            max = sales[i];
        }
    }
    return max;
}

int main() {
    FILE *file;
    int count = 0;
    float value;

    // Abrir el archivo en modo lectura
    file = fopen("sales.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Contar el número de líneas (ventas registradas)
    while (fscanf(file, "%f", &value) == 1) {
        count++;
    }

    // Reservar memoria dinámica para las ventas
    float *sales = (float *)malloc(count * sizeof(float));
    if (sales == NULL) {
        printf("Error al asignar memoria.\n");
        fclose(file);
        return 1;
    }

    // Volver al inicio del archivo para leer los valores
    rewind(file);

    // Leer los valores dentro del arreglo dinámico
    for (int i = 0; i < count; i++) {
        fscanf(file, "%f", &sales[i]);
    }

    // Calcular total y máximo
    float total = totalSale(sales, count);
    float max = maxSale(sales, count);

    // Imprimir resultados
    printf("Total de ventas: %.2f\n", total);
    printf("Venta máxima: %.2f\n", max);

    // Liberar memoria y cerrar archivo
    free(sales);
    fclose(file);

    return 0;
}
