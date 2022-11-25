#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int *items;
    int size;
}vector_t;

vector_t *vector_ctor(){
    vector_t *vec = (vector_t *)malloc(sizeof(vector_t));
    if (vec!=NULL){
        vec->size = 0;
    }
    return vec;
}
int *resize(int *arr,int new_size){
    int *new_arr = (int *)realloc (arr,new_size * sizeof(int));
    if (new_arr == NULL){
        free(arr);
        return NULL;
    }
    return new_arr;
}

int vector_add(vector_t *vec,int value){
    vec->items = resize(vec->items,vec->size + 1);
    if (vec->items == NULL ){
        return 0;
    }
    vec->items[vec->size]=value;
    vec->size +=1;
    return 1;
}
void vector_dtor(vector_t *vector){
    if (vector == NULL){
        return;
    }
    if (vector->items != NULL){
        free(vector->items);
    }
    free(vector);
}

int main(){
    //Konstrukce noveho vektoru
    vector_t *vec = vector_ctor();
    
    int num;
    //Precteni cisel z stdin
    while (scanf("%d",&num) == 1){
        if (!vector_add(vec,num)){
            vector_dtor(vec);
            return 1;
        }
    }
    printf("Vector = [ ");
    for (int i = 0; i<vec->size;i++){
        printf ("%d ", vec->items[i]);
    }
    printf("]\n");

    //cleanup
    vector_dtor(vec);
    return 0;
}
