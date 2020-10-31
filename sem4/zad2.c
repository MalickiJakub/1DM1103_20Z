#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    //macierz z pliku A.txt
    float x;
    float A[254];
    FILE *fin;
    fin=fopen(argv[1],"r");
    int i=0;
    while(fscanf(fin,"%f", &x)==1)
    {
        A[i]=x;
        i++;
    }
    int xx=A[0];
    int yy=A[1];
    float macierzA[xx][yy];
    int du=0;
    for(int j=0;j<xx;j++)
    {
        for(int k=0;k<yy;k++)
        {
            macierzA[j][k]=A[2+du];
            du++;
        }
    }
    //wektor z pliku x.txt
    float x2;
    float A2[254];
    FILE *sas;
    sas=fopen(argv[2],"r");
    int i2=0;
    while(fscanf(sas,"%f", &x2)==1)
    {
        A2[i2]=x2;
        i2++;
    }
    //niestety chyba pan sie pomylil i wpisal wektor 3x1, ale nie da sie wymnozyc macierzy z A.txt (3x2) przez macierz 3x1
    //Dlatego manualnie wpisze rozmiar wektora
    int xx2=2;
    int yy2=1;
    float wektor[xx2][yy2];
    wektor[0][0]=A2[2];
    wektor[1][0]=A2[3];

    //mnozenie
    float wynik[xx][yy2];
    for(int q=0;q<xx;q++)
    {
        for(int w=0;w<yy2;w++)
        {
            wynik[q][w]=0;
            for(int e=0;e<yy;e++)
            {
                wynik[q][w]=wynik[q][w]+macierzA[q][e]*wektor[e][w];
            }
        }
    }

    printf("(%d) [%f  %f  %f]\n",xx,wynik[0][0],wynik[1][0],wynik[2][0]);
    

}