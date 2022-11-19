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

void vytvorit(){

}
int main () {
    struct cluster_t *clusters;
    clusters[0].size=10;
    clusters[0].capacity=100;
    clusters[0].obj->id=1;
    clusters[0].obj->x=10;
    clusters[0].obj->y=20;

printf("%d %d %d %f %f",clusters[0].size,clusters[0].capacity,
        clusters[0].obj->id,clusters[0].obj->x,clusters[0].obj->y);

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