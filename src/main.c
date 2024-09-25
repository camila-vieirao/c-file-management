#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 100 
#define MIN_NUMBERS 30   


int compare(const void* a, const void* b) {
    return(*(int*)a - *(int*)b);    
}

// FONTE: https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/

int main() {

    // LENDO O ARQUIVO DE INPUT -------------------------------------------------------------------

    int k = 0;

    FILE* file = fopen("dados.txt", "r");
    if (file == NULL) {
        perror("Nao foi possível abrir o arquivo dados.txt");
        return 1;
    }

    fscanf_s(file, "%d", &k);

    // ---------->       PARA UTILIZAR LIMITE MAXIMO E MINIMO DE IMPUT, REMOVER ESTE COMENTARIO   <------------

    if (k < MIN_NUMBERS || k > MAX_CAPACITY) {
        fclose(file);
        return 1;
    }

    // FIM LIMITE INPUT
    
    int* n = (int*)malloc(k * sizeof(int));

    printf(" -=-=-=-=-=-=-=-=-=-=- DADOS.TXT -=-=-=-=-=-=-=-=-=-=-\n");

    printf("k: %d\nn: ", k);

    for (int i = 0; i < k; i++) {
        fscanf_s(file, "%d", &n[i]);
        printf("%d ", n[i]);
    }
    printf("\n");

    fclose(file);

    // OUTPUT: ESTATISTICAS.TXT  -------------------------------------------------------------------

    int pos_sum = 0, neg_sum = 0, zero_sum = 0, even_sum = 0, odd_sum = 0;

    for (int i = 0; i < k; i++) {
        if (n[i] > 0) pos_sum++;
        else if (n[i] < 0) neg_sum++;
        else zero_sum++;

        if (n[i] % 2 == 0) even_sum++;
        else odd_sum++;
    }

    FILE* statistics_file = fopen("estatisticas.txt", "w");
    if (statistics_file == NULL) {
        perror("Nao foi possível abrir o arquivo estatisticas.txt");
        return 1;
    }

    fprintf(statistics_file, "Quantidade de numeros positivos: %d\n", pos_sum);
    fprintf(statistics_file, "Quantidade de numeros negativos: %d\n", neg_sum);
    fprintf(statistics_file, "Quantidade de numeros zero: %d\n", zero_sum);
    fprintf(statistics_file, "Quantidade de numeros pares: %d\n", even_sum);
    fprintf(statistics_file, "Quantidade de numeros impares: %d\n", odd_sum);

    fclose(statistics_file);

    // OUTPUT: DISTINTOS.TXT  -------------------------------------------------------------------

    FILE* distinct_file = fopen("distintos.txt", "w");
    if (distinct_file == NULL) {
        perror("Nao foi possivel abrir o arquivo distintos.txt");
        return 1;
    }

    int counter = 0;
    int aux;

    int* distincts = (int*)malloc(k * sizeof(int));
    int distinct_count = 0;

    for (int i = 0; i < k; i++) {
        int is_distinct = 1;
        for (int j = 0; j < distinct_count; j++) {
            if (n[i] == distincts[j]) {
                is_distinct = 0; // Já está no array de distintos
                break;
            }
        }
        if (is_distinct) {
            distincts[distinct_count++] = n[i]; // Adiciona número distinto
            fprintf(distinct_file, "%d ", n[i]);
        }
    }

    fclose(distinct_file);

    // OUTPUT: ORDENADO.TXT  -------------------------------------------------------------------

    FILE* sorted_file = fopen("ordenados.txt", "w");
    if (sorted_file == NULL) {
        perror("Nao foi possivel abrir o arquivo ordenados.txt");
        free(n);
        return(1);
    }

    qsort(n, k, sizeof(int), compare);

    for (int i = 0; i < k; i++) {
        fprintf(sorted_file, "%d ", n[i]);
    }
    fclose(sorted_file);

    // OUTPUT: DISTINTOS_ORDENADO.TXT  -------------------------------------------------------------------

    FILE* sort_order_file = fopen("distintos_ordenados.txt", "w");
    if (sort_order_file == NULL) {
        perror("Nao foi possivel abrir o arquivo distintos_ordenados.txt");
        free(n);
        free(distincts);
        return 1;
    }

    qsort(distincts, distinct_count, sizeof(int), compare);

    for (int i = 0; i < distinct_count; i++) {
        fprintf(sort_order_file, "%d ", distincts[i]);
    }

    fclose(sort_order_file);

    free(n);
    free(distincts);

    return 0;
}