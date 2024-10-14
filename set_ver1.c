#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *v;
    int n;
} set;

typedef set* set_t;

int cmp (const void* a, const void* b){
    return (*(int*)a - *(int*) b);
}

void init(set_t m){
    m->n = 0;
    if (m->v != NULL) {
        free(m->v);
    }
    m->v = NULL;
}

void add_to_set (set_t m, int val){
    
    for (int i = 0; i < m->n; i++)
        if (m->v[i] == val)
            return;
        
    (m->n)++;
    m->v = realloc(m->v, sizeof(int) * m->n);
    (m->v)[m->n - 1] = val;
}

void remove_from_set (set_t m, int val){
    int poz = -1;
    for (int i = 0; i < m->n; i++)
        if (m->v[i] == val){
            poz = i;
            break;
        }
    
    if (poz == -1){
        printf("Elementul %d nu exista.\n", val);
        return;
    }

    for (int i = poz; i < m->n - 1; i++)
        m->v[i] = m->v[i + 1];
    
    m->v = realloc(m->v, sizeof(int) * (m->n - 1));
    (m->n)--;
}

void print_set(set m){
    if (m.n == 0){
        printf("Multimea nu are valori.\n");
        return;
    }

    for (int i = 0; i < m.n; i++)
        printf("%d ", m.v[i]);
    printf("\n");
}

void intersect(set a, set b){
    qsort(a.v, a.n, sizeof(int), cmp);
    qsort(b.v, b.n, sizeof(int), cmp);

    int i = 0, j = 0;
    printf("Intersectie: ");
    while (i < a.n && j < b.n) {
        if (a.v[i] < b.v[j]) {
            i++;
        } else if (b.v[j] < a.v[i]) {
            j++;
        } else {
            printf("%d ", a.v[i]);
            i++;
            j++;
        }
    }
    printf("\n");
}

void reunite (set a, set b){
    qsort(a.v, a.n, sizeof(int), cmp);
    qsort(b.v, b.n, sizeof(int), cmp); 

    int i = 0, j = 0;
    printf("Reuniune: ");
    while (i < a.n && j < b.n){
        if (a.v[i] < b.v[j]){
            printf("%d ", a.v[i]);
            i++;
        }
        else if (a.v[i] > b.v[j]) {
            printf("%d ", b.v[j]);
            j++;
        }
        else{
            printf("%d ", a.v[i]);
            i++;
            j++;
        }
    }

    while (i < a.n) {
        printf("%d ", a.v[i]);
        i++;
    }

    while (j < b.n) {
        printf("%d ", b.v[j]);
        j++;
    }
    printf("\n");
}

void belongs_to (set a, int nr){
    int poz = -1;

    for (int i = 0; i < a.n; i++){
        if (a.v[i] == nr){
            poz = i;
            break;
        }
    }

    if (poz == -1)
        printf("Nr. %d nu apartine multimii.\n", nr);
    else
        printf("Nr. %d apartine multimii.\n", nr);
}

int main (void){

    set A, B;
    A.v = NULL;
    B.v = NULL;

    init(&A);
    add_to_set(&A, 2);
    add_to_set(&A, 4);
    add_to_set(&A, 1);
    add_to_set(&A, 1);
    remove_from_set(&A, 4);
    add_to_set(&A, 5);

    init(&B);
    add_to_set(&B, 6);
    add_to_set(&B, 5);
    add_to_set(&B, 4);
    init(&B);
    add_to_set(&B, 1);
    add_to_set(&B, 11);

    print_set(A);
    print_set(B);
    intersect(A, B);
    belongs_to(A, 23);
    belongs_to(B, 11);


    init(&A);
    init(&B);
    add_to_set(&A, 2);
    add_to_set(&A, 5);
    add_to_set(&A, 9);
    add_to_set(&A, 11);
    add_to_set(&A, 7);

    add_to_set(&B, 5);
    add_to_set(&B, 11);
    add_to_set(&B, 7);
    add_to_set(&B, 23);
    add_to_set(&B, 34);
    add_to_set(&B, 17);

    print_set(A);
    print_set(B);
    reunite(A, B);    
    free(A.v);
    free(B.v);
    return 0;
}