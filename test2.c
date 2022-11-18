#include <stdio.h>
struct obj_t {
    int id;
    float x;
    float y;
};

// struct cluster_t {
//     int size;
//     int capacity;
//     struct obj_t *obj;
// };
int main(){
    printf("Hello world.\n");
    struct obj_t obj1;
    FILE * fPointer;
    fPointer = fopen("objekty.txt","r");
    char radek[50];
    while(!feof(fPointer)){
        int counter;
        fgets(radek,50,fPointer);
        if (counter!=0){
            sscanf(radek, "%d %f %f", &obj1.id,&obj1.x,&obj1.y);
            printf("Cluster %d: %d[%.1f, %.1f]\n",counter,obj1.id,obj1.x,obj1.y);
        }
        counter++;

    }
    fclose(fPointer);
    return 0;
}