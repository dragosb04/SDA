#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    struct nod* next;
    int value;
} node;

typedef node* set;
typedef set* set_t;

void free_set(set_t var){
    set p = *var;
    set temp;
    while (p != NULL){
        temp = p;
        p = p->next;
        free(temp);
    }
}

void init (set_t var){
    if (*var != NULL)
        free_set(var);
    *var = NULL;
}

set make_node (int val){

    set new = malloc(sizeof(node));
    new->value = val;
    new->next = NULL;

    return new;
}

void add_to_set(set_t var, int val){
    set p = *var;
    
    if (*var == NULL){
        *var = make_node(val);
        return;
    }

    if (p->value == val)
        return;

    while (p->next != NULL){
        if (p->value == val)
            return;
        
        p = p->next;
    }

    p->next = make_node(val);
}

void remove_from_set (set_t var, int val){
    if (*var == NULL) {
        printf("Multimea este goala.\n");
        return;
    }

    set p = *var;
    set prev = NULL; 

    while (p != NULL) {
        if (p->value == val) {
            if (prev == NULL) 
                *var = p->next;
            else 
                prev->next = p->next;
            free(p);
            return;
        }
        prev = p;
        p = p->next;
    }

    printf("Valoarea %d nu exista in multime.\n", val);
}

void print_set (set var){
    set p = var;

    while (p != NULL){
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

void intersect(set_t var1, set_t var2) {
    set p1 = *var1;

    printf("Intersectie: ");

    while (p1 != NULL) {
        set p2 = *var2;

        while (p2 != NULL) {
            if (p1->value == p2->value) {
                printf("%d ", p1->value);
                break;
            }
            p2 = p2->next;
        }

        p1 = p1->next;
    }
    printf("\n");
}

void reunite (set var1, set var2){
    set p = var1;
    set result = NULL;

    printf("Reuniune: ");
    while (p != NULL){
        add_to_set(&result, p->value);
        p = p->next;
    }

    p = var2;

    while (p != NULL){
        add_to_set(&result, p->value);
        p = p->next;
    }

    print_set(result);
    free_set(&result);
}

void belongs_to(set var, int val) {
    set p = var;

    while (p != NULL) {
        if (p->value == val) {
            printf("Valoarea %d exista in multime.\n", val);
            return;
        }
        p = p->next;
    }

    printf("Valoarea %d nu exista.\n", val);
}

int main (void){

    set A = NULL;
    init(&A);
    add_to_set(&A, 2);
    add_to_set(&A, 3);
    init(&A);
    add_to_set(&A, 2);
    add_to_set(&A, 7);
    remove_from_set(&A, 3);

    set B = NULL;
    init(&B);
    add_to_set(&B, 3);
    add_to_set(&B, 7);
    add_to_set(&B, 9);
    add_to_set(&B, 1);
    add_to_set(&B, 7);
    add_to_set(&B, 2);
    add_to_set(&B, 3);

    print_set(A);
    print_set(B);

    intersect(&A, &B);
    belongs_to(A, 4);
    belongs_to(B, 2);


    print_set(A);
    print_set(B);

    reunite(A, B);
    free_set(&A);
    free_set(&B);
    return 0;
}