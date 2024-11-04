#include <stdio.h>

void swap (int* a, int* b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

void printArr (int arr[], int n){
    for (int i = 0; i < n; i++)
        printf("%3d ", arr[i]);
    
    printf("\n");
}

void insertionSort (int arr[], int n){
    
    // O ia de la capat spre inceput si tot suprapune valoarea din fata pana ajunge la primul element mai mic decat elementul toCompare,
    // iar, la final, pune elementul toCompare pe ultima pozitie care a respectat conditia.
    // Pot avea [5, 1, 0, 9] -> [5, 5, 0, 9] -> [1, 5, 0, 9] -> [1, 5, 5, 9] -> [1, 1, 5, 9] (ajunge la pozitia 0) -> [0, 1, 5, 9]

    for (int i = 1; i < n; i++){
        int toCompare = arr[i];
        int index = i;

        for (int j = i - 1; j >= 0 && toCompare < arr[j]; j--){
            arr[j + 1] = arr[j];
            index = j;
            printArr(arr, n);
        }
        
        arr[index] = toCompare;
        printArr(arr, n);
        printf("\n");
    }

}

void selectionSort (int arr[], int n){

    // Ia mereu valoarea minima de la i la n - 1 (n - 1, pentru ca nu are rost sa compari ultimul element cu el insusi), si o pune pe pozitia i
    // [5, 1, 7, 3] - > [1, 5, 7, 3] -> [1, 3, 5, 7]
    //     ^                      ^            ^   

    for (int i = 0; i < n - 1; i++){

        int min_i = i;
        for (int j = i + 1; j < n; j++){
            if (arr[min_i] > arr[j])
                min_i = j;
        }
        swap(&arr[min_i], &arr[i]);
        printArr(arr, n);
    }
}

void bubbleSort (int arr[], int n){

    // Practic, ajunge sa "plimbe" cel mai mare numar pana la finalul array-ului. Se scade din numarul ultimei pozitii maxime,
    // deoarece se considera ca maximul la momentul i a fost descoperit si nu mai este nevoie sa mearga pana la final, ca deja este
    // pozitionat unde trebuie. In for-ul secundar, se tot verifica numerele de pe pozitii consecutive si se marcheaza cu swapped = 1,
    // daca are loc o modificare, altfel, va ramane pe swapped = 0, adica nu s-a modificat nimic, deci array-ul este sortat si opreste procesul.

    // i = 1; j = 1 : n - i - 1 => [5, 1, 7, 3] -> [1, 5, 7, 3] -> [1, 5, 3, 7]
    // i = 2; j = 1 : n - i - 1 => [1, 5, 3, 7] -> [1, 3, 5, 7] 

    int swapped = 1;

    for (int i = 0; i < n - 1; i++){
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        printArr(arr, n);
        if (!swapped)
            break;
    }

}

void shakerSort (int arr[], int n){

    // O ia de la stanga la dreapta si face operatiunea bubbleSort-ului de a muta elementul cel mai mare la final in primul for,
    // iar in al doilea for il muta pe cel mai mic la stanga mereu si face asta tot asa, pana nu mai respecta conditia de la for-ul principal.

    for (int i = 1; i <= n / 2; i++){
        for (int j = i - 1; j < n - i; j++)
            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
                printArr(arr, n);
            }
        printf("\n");
        for (int j = n - i - 1; j >= i; j--)
            if (arr[j - 1] > arr[j]){
                swap(&arr[j - 1], &arr[j]);
                printArr(arr, n);
            }

    }
}

int main (void){

    int arr[] = {2, 7, 12, 6, 11, 9, 0, 3};
    int n = sizeof(arr) / sizeof(int);
//    insertionSort(arr, sizeof(arr)/sizeof(int));
//    selectionSort(arr, n);
//    bubbleSort(arr, n);
    shakerSort(arr, n);
    printArr(arr, n);

    return 0;
}