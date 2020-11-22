#include "dziekanat.h"








int main(int argc, char ** argv) {
    student dane[100];

    int ile = wczytaj(dane, argv[2]);

    if(strcmp(argv[1],"najlepszy_student")==0)
    {
        najlepszy_student(dane,ile);
    }
    else
    {
        if(strcmp(argv[1],"najtrudniejszy_przedmiot")==0)
        {
             najlepszy_przedmiot(dane, ile);
        }
        else{
            printf("Nieznana komenda, poprawne wywolanie programu: ./zad5 {funkcja} {plik z danymi}\nfunkcje:\nnajlepszy_student\nnajtrudniejszy_przedmiot\n");
        }
    }


    return 0;
}