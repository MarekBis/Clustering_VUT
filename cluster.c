/**
 * Kostra programu pro 2. projekt IZP 2022/23
 *
 * Jednoducha shlukova analyza: 2D nejblizsi soused.
 * Single linkage
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu:
 *       identifikator a souradnice
 * 
 *   struct cluster_t - shluk objektů:
 *      pocet objektů ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

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

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);

    c->obj = malloc(sizeof(struct obj_t)*cap);

    if (c->obj != NULL){
        c->capacity = cap;
        c->size = 0;
    }else{
        fprintf(stderr,"Malloc c->obj error.\n");
    }
}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
    free(c->obj);

    c->obj = NULL;
    c->size = 0;
    c->capacity = 0;
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t*)arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
    //Pokud v clusteru již není místo, zvětšíme capacitu o CLUSTER_CHUNK
    if (c->size == c->capacity){
        resize_cluster(c,c->size + CLUSTER_CHUNK);
    }
    //Prirazeni objektu do shluku
    c->obj[c->size] = obj;
    c->size++;
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);
    //vyuzitim funkce pridame kazdy objekt z c2 do c1
    for (int i = 0; i<c2->size;i++){
        append_cluster(c1,c2->obj[i]);
    }
    //Následně seřadíme
    sort_cluster(c1);
}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);
    //Odstraníme vybraný shluk pomocí idx z pole shluků
    clear_cluster(&carr[idx]);
    //Následně posuneme všechny prvky které v poli následovali o jedno zpátky
    for (int i = idx;i < narr - 1 ;i++){
        carr[i] = carr[i+1];
    }
    //Vrátíme novou hodnotu počtu shluků v poli
    return narr - 1;

}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    float distance;

    float aX = o1->x;
    float aY = o1->y;

    float bX = o2->x;
    float bY = o2->y;

    distance = sqrtf((((bX - aX) * (bX - aX)) + ((bY - aY) * (bY - aY))));
    return distance;
}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);
    //Nastavíme vzdálenost pro 2 libovolné prvky v poli
    float clusterDistance = obj_distance(&(c1->obj[0]),&(c2->obj[0]));
    //Inicializujeme proměnnou, do které budeme zapisovat nejmenší vzdálenost
    float newDistance;
    //Budeme procházet všechny prvky prvního, následně druhého clusteru
    for (int indexC1 = 0; indexC1 < c1->size; indexC1++){
        for (int indexC2 = 0; indexC2 < c2->size; indexC2++){
            //Vypočítáme vzdálenost
            newDistance = obj_distance(&(c1->obj[indexC1]),&(c2->obj[indexC2]));
            //Pokud je nově nalezená vzdálenost menší než předešlá, přepíšeme ji
            if ( newDistance < clusterDistance ){
                clusterDistance = newDistance;
            }
        }
    }
    //Vracíme nejmenší vzdálenost
    return clusterDistance;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'clusterArr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'clusterArr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);
    //Znovu jako u cluster_distance nastavíme vzdálenost mezi libovolné prvky
	float neighbourDistance = cluster_distance(&(carr[0]), &(carr[1]));
    float newDistance;
    //Procházíme všechny prvky v i arrayi
    for(int i = 0; i < narr - 1; i++){
        //Projdeme všechny prvky, které ještě nebyly porovnány
		for(int j = i + 1; j < narr; j++){
            //Výpočet
			newDistance = cluster_distance(&(carr[i]),&(carr[j]));
            //Pokud je nově nalezená vzdálenost menší než předešlá, nebo se rovná, přepíšeme ji 
			if (newDistance <= neighbourDistance)
			{
                //Přepíšeme proměnnou
				neighbourDistance = newDistance;
                //Vrátíme indexy "i" a "j" jako c1,c2
				*c1 = i;
				*c2 = j;
			}
		}
	}
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
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

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).

 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);

    //Otevreni a kontrola souboru
    FILE *filePtr;
    filePtr = fopen(filename,"r");
    //Zjistíme, jestli se soubor správně otevřel, pokud ne, vypíšeme error.
    if (filePtr == NULL){
        fprintf(stderr,"Error: nepodarilo se otevrit soubor.\n");
        *arr=NULL;
        return -1;
    }
    //Vytvoříme strukturu obj_t a potřebné proměnné
    struct obj_t object;
    char countText[7]; //První řádek, potřebné k uložení "count="
    int countNumber; //Počet objektů v souboru
    int loadedObjects = 0;

    //nacteni prvniho radku kvuli "countNumber",
    //Zjisteni jestli se hlavicka spravne nacetla ( fscanf == 2 )
    if (fscanf(filePtr,"%6s%d", countText,&countNumber) !=2){
        fprintf(stderr,"Error: spatny format hlavicky souboru.\n");
        *arr=NULL;
        fclose(filePtr);
        return -1;
    };
    //Počet objektů se nemůže rovnat nebo být menší jak 0
    if (countNumber <= 0){
        fprintf(stderr,"Error: pocet objektu nemuze byt mensi/rovno 0");
        *arr=NULL;
        return -1;
    }
    //Vytvoreni seznamu ID's pro pozdejsi kontrolu unikatnosti
        char uniqueIds[countNumber];
    //alokace místa pro všechny objekty v souboru
    *arr = malloc(sizeof(struct cluster_t) * countNumber);

    /*Prace s objekty*/

    for (int i = 0; i<countNumber;i++){
        //načtene ID a souřadnice ze souboru, pokud se některé z čísel nenačte, vyhodnotíme ERROR
        if (fscanf(filePtr,"%d %f %f",&object.id,&object.x,&object.y) != 3){
            fprintf(stderr,"Error: Spatny format objektu v souboru.\n");
            for (int i=0; i<loadedObjects; i++) {
                clear_cluster(&(*arr)[i]);
            }
            free(*arr);
            *arr=NULL;
            fclose(filePtr);
            return -1;
        }else{
            loadedObjects++;
        }
        //pokud má souřadnice více jak 1000, nebo méně než 0, error
        if (object.x > 1000 || object.x < 0 || object.y > 1000 || object.y < 0){
            fprintf(stderr,"Error: Souradnice nejsou ve spravnem rozsahu\n");
            for (int i=0; i<loadedObjects-1; i++) {
                clear_cluster(&(*arr)[i]);
            }
            fclose(filePtr);
            free(*arr);
            *arr=NULL;
            return -1;
        }
        //přiřazení ID do seznamu
        int uniqueID =object.id;
        uniqueIds[i] = uniqueID;
        //inicializace a přidání daného objektu do carr
        init_cluster(&(*arr)[i],1);
        append_cluster(&(*arr)[i],object);
    }
    //zkontrolujeme jestli seznam ID's neobsahuje identické ID
    for (int i = 0;i<countNumber -1;i++){
        for (int j = i+1; j < countNumber; j++){
            if (uniqueIds[i] == uniqueIds[j]){
                fprintf(stderr,"Error: Objekty maji stejne ID\n");
                for (int i=0; i<countNumber; i++) {
                    clear_cluster(&(*arr)[i]);
                }
                fclose(filePtr);
                free(*arr);
                *arr=NULL;
                return -1;
            }
        }
    }
    if (loadedObjects != countNumber){
        fprintf(stderr,"Error: Nenacetly se vsechny objekty\n");
        for (int i=0; i<countNumber; i++) {
            clear_cluster(&(*arr)[i]);
        }
        fclose(filePtr);
        free(*arr);
        *arr=NULL;
        return -1;
    }
    fclose(filePtr);
    return countNumber;

}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main(int argc, char *argv[])
{
    struct cluster_t *clusters;
    int numberOfClusters;

    //Přiřazení čísla numberOfClusters podle argumentu
    if (argc == 3){
        numberOfClusters = atoi(argv[2]);
    //pokud se agrument nenachází nastavujeme počet clusterů na 1
    }else if (argc == 2){
        numberOfClusters = 1;
    }else{
        fprintf(stderr,"Error: nespravny pocet argumentu.\n");
        return -1;
    }
    //inicializace indexů (podle šablony c1,c2)
    int c1,c2 = 0;
    int clustersLoaded = load_clusters(argv[1],&clusters);
    //pokud je error v načítání clusterů, program se ukončí
    if (clustersLoaded == -1){
        fprintf(stderr,"Error: nepodarilo se nacist clustery.\n");
        return -1;
    }
    
    /***Algoritmus,print a následné uvolnění clusterů***/

    while (clustersLoaded!=numberOfClusters) {

        find_neighbours(clusters, clustersLoaded, &c1, &c2);

        merge_clusters(&clusters[c1],&clusters[c2]);

        clustersLoaded = remove_cluster(clusters, clustersLoaded, c2);
	}

    print_clusters(clusters,clustersLoaded);
    for (int i=0; i<clustersLoaded; i++) {
        clear_cluster(&clusters[i]);
    }
    free(clusters);
	return 0;
}