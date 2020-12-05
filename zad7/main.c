#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

int main(int argc, char ** argv) {
    SBaza *baza = wczytaj_baze(argv[1]);
    if (strcmp("add_course", argv[2]) == 0) {
        dodajPrzedmiot(baza, argv[3], argv[4], argv[5]);
        zapisz_baze(argv[6], baza); 
    } else if (strcmp("add_student", argv[2]) == 0) {
        dodajStudenta(baza, argv[3], argv[4], argv[5], argv[6]);
        zapisz_baze(argv[7], baza);
    } else if (strcmp("add_student_to_course", argv[2]) == 0) {
        dodajOcene(baza,argv[3],argv[4],atof(argv[5]),argv[6]);
        zapisz_baze(argv[7], baza); 
    }
    zwolnij(baza);
    //printf("%s\n%s\n%s\n%s\n",argv[1],argv[2],argv[3],argv[4]);
    return 0;
}