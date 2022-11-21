#include <stdio.h>
#include <stdlib.h>
struct obj_t {
    int id;
    float x;
    float y;
};
struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};


int main(){
    printf("Hello World.\n");

    int lenght = 20;
    struct obj_t *array;
    array = malloc(sizeof(struct obj_t)*lenght);

    char countText[7];
    int number;
    FILE * FilePtr;
    FilePtr = fopen ("objekty.txt", "r");
    fscanf(FilePtr,"%6s%d",countText,&number);
    for (int i = 0;i<number;i++){
        fscanf(FilePtr,"%d %f %f",&array[i].id,&array[i].x,&array[i].y);
        printf("Cluster %d: %d[%.0f, %.0f]\n",i,array[i].id,array[i].x,array[i].y);
        }
    fclose(FilePtr);
    free(array);
    return 0;
}