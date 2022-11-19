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
/*
 Inicializace shluku 'c'. Alokuje pamet pro kapacitu objektu (cap).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap){
    // TODO
}
int main () {
    struct cluster_t *clusters;




    struct obj_t obj1;
    struct cluster_t clust1;
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