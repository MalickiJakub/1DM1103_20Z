#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

struct macierz
{
int m;
int n;
float tab[254][254];
};

int czyJuzWykonanoJakiesDzialanie=0;

void wczytaj(FILE *fin, struct macierz *mac) {
    fscanf(fin, "%d", &mac->m);
    fscanf(fin, "%d", &mac->n);

    for (int i=0; i < mac->m ; i++) {
        for (int j=0; j < mac->n; j++) {
            fscanf(fin, "%f", &mac->tab[i][j]);
        }
    }
}

struct macierz subtract(struct macierz mac1, struct macierz mac2)
{
    struct macierz wynik;
    wynik.m=mac1.m;
    wynik.n=mac1.n;
    for(int i=0;i<mac1.m;i++)
    {
        for(int j=0;j<mac1.n;j++)
        {
            wynik.tab[i][j]=mac1.tab[i][j]-mac2.tab[i][j];
        }
    }
    return wynik;
}

struct macierz sum(struct macierz mac1, struct macierz mac2)
{
    struct macierz wynik;
    wynik.m=mac1.m;
    wynik.n=mac1.n;
    for(int i=0;i<mac1.m;i++)
    {
        for(int j=0;j<mac1.n;j++)
        {
            wynik.tab[i][j]=mac1.tab[i][j]+mac2.tab[i][j];
        }
    }
    return wynik;
}

float norm(struct macierz mac)
{
    float wynik=0;
    for(int i=0;i<mac.m;i++)
    {
        for(int j=0;j<mac.n;j++)
        {
            wynik+=mac.tab[i][j];
        }
    }
    return sqrt(wynik);
}

struct macierz multiply(float skalar, struct macierz mac)
{
    struct macierz wynik;
    wynik.m=mac.m;
    wynik.n=mac.n;
    for(int i=0;i<mac.m;i++)
    {
        for(int j=0;j<mac.n;j++)
        {
            wynik.tab[i][j]=mac.tab[i][j]*skalar;
        }
    }

    return wynik;
}

struct macierz prod(struct macierz mac1, struct macierz mac2)
{
    struct macierz wynik;
    wynik.m=mac1.m;
    wynik.n=mac2.n;
    for(int i=0;i<mac1.m;i++)
    {
        for(int j=0;j<mac2.n;j++)
        {
            wynik.tab[i][j]=0;
            for(int k=0;k<mac1.n;k++)
            {
                wynik.tab[i][j]+=mac1.tab[i][k]*mac2.tab[k][j];
            }
        }
    }
    return wynik;
}

void zapiszDoPliku(struct macierz mac,char nazwa[])
{
    FILE *zapis=fopen(nazwa,"w");
    fprintf(zapis,"%d\n%d\n",mac.m,mac.n);
    for(int i=0;i<mac.m;i++)
    {
        for(int j=0;j<mac.n;j++)
        {
            fprintf(zapis,"%f  ",mac.tab[i][j]);
        }
        fprintf(zapis,"\n");
    }

}

void wypiszBoNiePodanoPlikuKoncowego(struct macierz mac)
{
    for(int i=0;i<mac.m;i++)
    {
        for(int j=0;j<mac.n;j++)
        {
            printf("%.3f  ",mac.tab[i][j]);
        }
        printf("\n");
    }
}

struct macierz zamienLiczbeNaMacierz1x1(float a)
{
    struct macierz wynik;
    wynik.m=1;
    wynik.n=1;
    wynik.tab[0][0]=a;
    return wynik;
}

int main(int argc, char *argv[])
{


    if((strcmp(argv[1],"sum")==0)&&(czyJuzWykonanoJakiesDzialanie==0))
    {
        struct macierz A;
        struct macierz x;
        FILE *finA=fopen(argv[2],"r");
        FILE *finx=fopen(argv[3],"r");
        wczytaj(finA,&A);
        wczytaj(finx,&x);
        if(A.m==x.m&&A.n==x.n)
        {
            if(argc==5)
            {
                zapiszDoPliku(sum(A,x),argv[4]);
            }
            else
            {
                wypiszBoNiePodanoPlikuKoncowego(sum(A,x));
            }
        }
        else
        {
            printf("Rozmiary macierzy sie nie zgadzaja.\nNie mozna wykonac operacji\n");
        }
        czyJuzWykonanoJakiesDzialanie=1;
          fclose(finA);
          fclose(finx);
    }



    if((strcmp(argv[1],"subtract")==0)&&(czyJuzWykonanoJakiesDzialanie==0))
        {
            struct macierz A;
            struct macierz x;
            FILE *finA=fopen(argv[2],"r");
            FILE *finx=fopen(argv[3],"r");
            wczytaj(finA,&A);
            wczytaj(finx,&x);
            if(A.m==x.m&&A.n==x.n)
            {
                if(argc==5)
                {
                    zapiszDoPliku(subtract(A,x),argv[4]);
                }
                else
                {
                    wypiszBoNiePodanoPlikuKoncowego(subtract(A,x));
                }
            }
            else
            {
                printf("Rozmiary macierzy sie nie zgadzaja.\nNie mozna wykonac operacji\n");
            }
            czyJuzWykonanoJakiesDzialanie=1;
          fclose(finA);
          fclose(finx);
        }
    


    if((strcmp(argv[1],"prod")==0)&&(czyJuzWykonanoJakiesDzialanie==0))
        {
            struct macierz A;
            struct macierz x;
            FILE *finA=fopen(argv[2],"r");
            FILE *finx=fopen(argv[3],"r");
            wczytaj(finA,&A);
            wczytaj(finx,&x);
            if(A.n==x.m)
            {
                if(argc==5)
                {
                    zapiszDoPliku(prod(A,x),argv[4]);
                }
                else
                {
                    wypiszBoNiePodanoPlikuKoncowego(prod(A,x));
                }
            }
            else
            {
                printf("Rozmiary macierzy sie nie zgadzaja.\nNie mozna wykonac operacji\n");
            }
            czyJuzWykonanoJakiesDzialanie=1;
          fclose(finA);
          fclose(finx);
        }

    

    if((strcmp(argv[1],"multiply")==0)&&(czyJuzWykonanoJakiesDzialanie==0))
        {
            struct macierz A;
            float x;
            FILE *finA=fopen(argv[2],"r");
            x=atof(argv[3]);
            wczytaj(finA,&A);
                if(argc==5)
                {
                    zapiszDoPliku(multiply(x,A),argv[4]);
                }
                else
                {
                    wypiszBoNiePodanoPlikuKoncowego(multiply(x,A));
                }
            czyJuzWykonanoJakiesDzialanie=1;
          fclose(finA);
        }
    
    

    if((strcmp(argv[1],"norm")==0)&&(czyJuzWykonanoJakiesDzialanie==0))
        {
            struct macierz A;
            FILE *finA=fopen(argv[2],"r");
            wczytaj(finA,&A);
                if(argc==4)
                {
                    zapiszDoPliku(zamienLiczbeNaMacierz1x1(norm(A)),argv[3]);
                }
                else
                {
                    wypiszBoNiePodanoPlikuKoncowego(zamienLiczbeNaMacierz1x1(norm(A)));
                }
            czyJuzWykonanoJakiesDzialanie=1;
            fclose(finA);
        }


    if(czyJuzWykonanoJakiesDzialanie==0)
    {
        printf("Nie rozpoznano takiej operacji\n");
    }    
    return 0;
}