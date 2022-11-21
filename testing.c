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
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);

    // TODO
    FILE * filePointer;
    int count = 20; 
    filePointer = fopen ("objekty.txt", "r");
    for (int radek = 0;radek<=count;radek++){
        if (radek !=0){
        fscanf(filePointer,"%d %f %f",);
        printf("Cluster %d: %d[%.1f, %.1f]\n",radek,obj1.id,obj1.x,obj1.y);
        }else{
            fscanf(filePointer,"%s",count);
            printf("%s\n",count);
        }
    }
    fclose(filePointer);
}

void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

void print_clusters(struct cluster_t *carr, int narr){
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main () {
    int n;
    struct cluster_t *clusters;    


   
   
   return 0;
}