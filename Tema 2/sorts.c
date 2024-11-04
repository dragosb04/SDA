#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int age;
    float salary;
} data;

void swap(data* a, data* b) {
    data temp = *a;
    *a = *b;
    *b = temp;
}

data* inputRec(FILE* f, int* size) {
    int capacity = 10;
    data* rec = malloc(capacity * sizeof(data));

    if (!rec) {
        printf("Alocare esuata.\n");
        exit(1);
    }

    *size = 0;
    while (fscanf(f, "%49[^,],%d,%f\n", rec[*size].name, &rec[*size].age, &rec[*size].salary) == 3) {
        (*size)++;
        
        if (*size >= capacity) {
            capacity *= 2;
            rec = realloc(rec, capacity * sizeof(data));
            
            if (!rec) {
                printf("Alocare esuata.\n");
                exit(1);
            }
        }
    }

    return rec;
}

void outputRec(data rec[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Nume: %s ", rec[i].name);
        printf("Varsta: %d ", rec[i].age);
        printf("Salariu: %.2f\n", rec[i].salary);
    }
}

void insertionSort(data rec[], int size) {
    data* temp = malloc(size * sizeof(data));
    if (!temp) {
        printf("Alocare esuata.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        temp[i] = rec[i];

    clock_t start, end;
    double time_exec;

    start = clock();
    
    for (int i = 1; i < size; i++) {
        data key = temp[i];
        int j = i - 1;

        while (j >= 0 && temp[j].age > key.age) {
            temp[j + 1] = temp[j];
            j--;
        }

        temp[j + 1] = key;
    }

    end = clock();
    time_exec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sortare prin insertionSort: %f sec\n", time_exec);
    free(temp);
}

void selectionSort(data rec[], int size) {
    data* temp = malloc(size * sizeof(data));
    if (!temp) {
        printf("Alocare esuata.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        temp[i] = rec[i];

    clock_t start, end;
    double time_exec;

    start = clock();

    for (int i = 0; i < size - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < size; j++) {
            if (temp[j].age < temp[min_i].age)
                min_i = j;
        }
        swap(&temp[i], &temp[min_i]);
    }

    end = clock();
    time_exec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sortare prin selectionSort: %f sec\n", time_exec);
    free(temp);
}

void bubbleSort(data rec[], int size) {
    data* temp = malloc(size * sizeof(data));
    if (!temp) {
        printf("Alocare esuata.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        temp[i] = rec[i];
    
    clock_t start, end;
    double time_exec;

    bool swapped;

    start = clock();

    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (temp[j].age > temp[j + 1].age) {
                swap(&temp[j], &temp[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }

    end = clock();
    time_exec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sortare prin bubbleSort: %f sec\n", time_exec);
    free(temp);
}

void shakerSort(data rec[], int size) {
    data* temp = malloc(size * sizeof(data));
    if (!temp) {
        printf("Alocare esuata.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
        temp[i] = rec[i];

    clock_t start, end;
    double time_exec;

    start = clock();

    for (int p = 1; p <= size / 2; p++) {
        for (int i = p - 1; i < size - p; i++)
            if (temp[i].age > temp[i + 1].age)
                swap(&temp[i], &temp[i + 1]);
        
        for (int i = size - p - 1; i >= p; i--)
            if (temp[i].age < temp[i - 1].age)
                swap(&temp[i], &temp[i - 1]);
    }

    end = clock();
    time_exec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sortare prin shakerSort: %f sec\n", time_exec);
    free(temp);
}

int main(void) {
    FILE* f = fopen("angajati.csv", "r");
    if (f == NULL) {
        printf("Eroare la citire.\n");
        return 1;
    }

    int size;
    data* rec = inputRec(f, &size);
    fclose(f);

//    outputRec(rec, size);

    insertionSort(rec, size);
    selectionSort(rec, size);
    bubbleSort(rec, size);
    shakerSort(rec, size);

    free(rec);
    return 0;
}
