#include <stdio.h>
#include <limits.h>

#define MAXSIZE 100

/* ======= Max-Heap (array-based) ======= */
static int heap[MAXSIZE];
static int n = 0;               // número de elementos en el heap

/* índices relación padre/hijos (slides) */
static inline int left (int i) { return 2*i + 1; }
static inline int right(int i) { return 2*i + 2; }
static inline int parent(int i){ return (i - 1) / 2; }

static inline void swap(int *a, int *b){ int t = *a; *a = *b; *b = t; }

/* ----- reHeapUp: burbujea hacia arriba para mantener Max-Heap ----- */
void reHeapUp(int i){
    while(i > 0){
        int p = parent(i);
        if(heap[i] > heap[p]){ swap(&heap[i], &heap[p]); i = p; }
        else break;
    }
}

/* ----- reHeapDown: burbujea hacia abajo para mantener Max-Heap ----- */
void reHeapDown(int i){
    while(left(i) < n){
        int l = left(i), r = right(i);
        int largest = l;
        if(r < n && heap[r] > heap[l]) largest = r;
        if(heap[largest] > heap[i]){ swap(&heap[largest], &heap[i]); i = largest; }
        else break;
    }
}

/* ----- insert: agrega y reordena ----- */
void insert(int item){
    if(n >= MAXSIZE){ printf("Heap overflow\n"); return; }
    heap[n] = item;
    reHeapUp(n);
    n++;
}

/* ----- removeMax: quita y regresa la raíz ----- */
int removeMax(void){
    if(n == 0){ printf("Heap underflow\n"); return INT_MIN; }
    int maxv = heap[0];
    heap[0] = heap[--n];      // mover último a la raíz
    if(n > 0) reHeapDown(0);  // reacomodar
    return maxv;
}

/* ----- showHeap: imprime arreglo del heap ----- */
void showHeap(void){
    printf("heap[%d]: ", n);
    for(int i=0;i<n;i++){
        printf("%d", heap[i]);
        if(i+1<n) printf(" ");
    }
    printf("\n");
}

/* ----- showNodeChildren: mapeo arreglo↔árbol por índices ----- */
void showNodeChildren(void){
    printf("\nIndex  Val  |  L(i) Val  R(i) Val\n");
    printf("----------------------------------\n");
    for(int i=0;i<n;i++){
        int li = left(i), ri = right(i);
        printf("%5d %4d  |", i, heap[i]);
        if(li < n) printf(" %4d %4d", li, heap[li]);
        else       printf("  ---  ---");
        if(ri < n) printf("  %4d %4d", ri, heap[ri]);
        else       printf("   ---  ---");
        printf("\n");
    }
    printf("\n");
}

/* ======= Demo: inserta, muestra tras cada inserción; quita K veces ======= */
int main(void){
    int data[] = {42, 35, 23, 27, 21, 22, 4, 19, 45};
    int m = sizeof(data)/sizeof(data[0]);
    int K = 3;  // número de removals (puedes cambiarlo)

    printf("== Insertions ==\n");
    for(int i=0;i<m;i++){
        insert(data[i]);
        printf("insert(%d) -> ", data[i]);
        showHeap();                // imprime después de cada inserción
    }
    showNodeChildren();            // mapeo arreglo↔árbol (índices e hijos)

    printf("== Remove-Max %d times ==\n", K);
    for(int k=0;k<K;k++){
        int x = removeMax();
        printf("removeMax() = %d -> ", x);
        showHeap();                // imprime después de cada eliminación
    }
    showNodeChildren();

    return 0;
}
