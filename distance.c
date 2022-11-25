#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    float x;
    float y;
}bod;

void swapSouradnic(bod *a){
    float temp;
    temp = a->x;
    a->x = a->y;
    a->y = temp;
}
void swapBodu(bod *a, bod*b){
    float tempX; float tempY;

    tempX = a->x;tempY = a->y;

    a->x = b->x; a->y = b->y;

    b->x = tempX; b->y = tempY;
}
float distanceBetween(bod a, bod b){
    float distance;
    distance = sqrt(((b.x - a.x) * (b.x - a.x) + ((b.y - a.y) * (b.y - a.y))));
    return distance;
}

int main(){
    bod a ={
        10.0,
        10.0
    };
    bod b = {
        5.0,
        5.0
    };
    printf("Souradnice bodu a jsou: (%0.2f, %0.2f)\n",a.x,a.y);
    printf("Souradnice bodu b jsou: (%0.2f, %0.2f)\n",b.x,b.y);
    printf("Vzdalenost mezi body 'a' a 'b' je: %.2f b\n",distanceBetween(a,b));
    int pole[10]; //pole deseti celych cisel
    int* ukazatel; //ukazatel na cela cisla
    ukazatel = malloc (1* sizeof(int)); //alokujeme misto pro 10 celych cisel
    
    if(ukazatel != NULL) //pokud se alokace podarila
    {
    printf("Velikost pole je %d\n", sizeof(pole)); //vypis
    printf("Velikost ukazatele je %d\n", sizeof(ukazatel)); //vypis
    free(ukazatel); //uvolnujeme alokovanou pamet 
    }

}