#include <stdio.h>

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
int main () {
    struct obj_t obj1;
    FILE * filePointer;
    char count[20];
   filePointer = fopen ("objekty.txt", "r");
    for (int radek = 0;radek<=20;radek++){
        if (radek !=0){
        fscanf(filePointer,"%d %f %f", &obj1.id,&obj1.x,&obj1.y);
        printf("Cluster %d: %d[%.1f, %.1f]\n",radek,obj1.id,obj1.x,obj1.y);
        }else{
            fscanf(filePointer,"%s",count);
            printf("%s\n",count);
        }
    }


   fclose(filePointer);
   
   return 0;
}