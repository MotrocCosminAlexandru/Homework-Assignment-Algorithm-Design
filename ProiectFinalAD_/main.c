#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Homar
{
    int id;
    int lungime;
    int valoare;
};
float valoareaPerUnitate(struct Homar Homari)
{
    return Homari.valoare / (Homari.lungime * 1.0);
}
void sortareHomari(struct Homar *Homari, int noHomari)
{
    int iterator1;
    int iterator2;
    int indexMin;
    int auxSize;
    int auxId;
    int auxValue;

    for(iterator1 = 0; iterator1 < noHomari - 1; iterator1++){
        indexMin = iterator1;
        for(iterator2 = iterator1 + 1; iterator2 < noHomari; iterator2++){
            if (valoareaPerUnitate(Homari[indexMin]) < valoareaPerUnitate(Homari[iterator2]) ){
                indexMin = iterator2;
            }
        }
        if (indexMin != iterator1){
            auxSize = Homari[indexMin].lungime;
            auxId = Homari[indexMin].id;
            auxValue = Homari[indexMin].valoare;
            Homari[indexMin].lungime = Homari[iterator1].lungime;
            Homari[indexMin].id = Homari[iterator1].id;
            Homari[indexMin].valoare = Homari[iterator1].valoare;
            Homari[iterator1].lungime = auxSize;
            Homari[iterator1].id = auxId;
            Homari[iterator1].valoare = auxValue;
        }
    }
}
void repartizareHomari(struct Homar *Homari, int noHomari, int dimensiunePlasa)
{
    int iterator = 0;
    int dimensiunePlasaMomentan = dimensiunePlasa;
    float valoarePlasa = 0.0;

    for(iterator = 0; iterator < noHomari && dimensiunePlasaMomentan > 0; iterator++){
        if(Homari[iterator].lungime <= dimensiunePlasaMomentan){
            printf("\nA fost ales Homarul nr.%d, cu valoarea:%d si lungimea:%d",Homari[iterator].id,Homari[iterator].valoare,Homari[iterator].lungime);
            valoarePlasa += Homari[iterator].valoare;
            dimensiunePlasaMomentan -= Homari[iterator].lungime;
        }
    }
    printf("\nValoarea maxima obtinuta: %f", valoarePlasa);
}

void generareHomarii(struct Homar *Homari, int noHomari)
{
    int iterator;
    for(iterator = 0; iterator < noHomari; iterator++)
    {
        Homari[iterator].id = iterator;
        Homari[iterator].lungime = rand()%500+1;
        Homari[iterator].valoare = rand()%500+1;
    }
}
int generateNumbers()
{
    int generatedNumber=rand()%10000+1;
    return generatedNumber;
}

int main()
{
    srand(time(NULL));
    clock_t tic = clock();
    struct Homar *Homari;
    int noHomari=generateNumbers();
    int DimensiunePlasa=generateNumbers();
    Homari = malloc(noHomari * sizeof(struct Homar));
    generareHomarii(Homari, noHomari);


    printf("  Numarul de homari:%d\n  Marimea plasei:%d", noHomari, DimensiunePlasa);
    printf("\n==== Homari selectati====  ");
    sortareHomari(Homari, noHomari);
    repartizareHomari(Homari, noHomari, DimensiunePlasa);
    clock_t toc = clock();
    printf("\nElapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}
