#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

int main(int argc, char ** argv) {
    SBaza *baza = wczytaj_baze(argv[1]);

    //*

    if (strcmp("add_course", argv[2]) == 0) {
        dodajPrzedmiot(baza, argv[3], argv[4], argv[5]);
        zapisz_baze(argv[6], baza); 
    } else if (strcmp("add_student", argv[2]) == 0) {
        dodajStudenta(baza, argv[3], argv[4], argv[5], argv[6]);
        zapisz_baze(argv[7], baza);
    } else if (strcmp("add_student_to_course", argv[2]) == 0) {
        dodajOcene(baza,argv[3],argv[4],atof(argv[5]),argv[6]);
        zapisz_baze(argv[7], baza); 
    } else if (strcmp("student_grades", argv[2]) == 0) {
        oceny_studenta(argv[3],baza->lista_ocen);
    } else if (strcmp("course_grades", argv[2]) == 0) {
        oceny_przedmiotu(argv[3],baza->lista_ocen);
    } else if (strcmp("sort_students_backwards", argv[2]) == 0) {
        wypisz_rekurencyjnie_stud(sortuj_stud_od_konca(baza->lista_studentow));
    } else if (strcmp("sort_students", argv[2]) == 0) {
        wypisz_rekurencyjnie_od_konca_stud(sortuj_stud_od_konca(baza->lista_studentow));
    } else if (strcmp("sort_courses_by_name", argv[2]) == 0) {
        wypisz_rekurencyjnie_przed(sortuj_przed_nazwa(baza->lista_przedmiotow));
    } else if (strcmp("sort_courses_by_code", argv[2]) == 0) {
        wypisz_rekurencyjnie_przed(sortuj_przed_kod(baza->lista_przedmiotow));
    }

    //*/
   //wypisz_rekurencyjnie_od_konca_stud(sortuj_stud_od_konca(baza->lista_studentow));
    //wypisz_rekurencyjnie_przed(sortuj_przed_nazwa(baza->lista_przedmiotow));
    //wypisz_rekurencyjnie_przed(sortuj_przed_kod(baza->lista_przedmiotow));
    zwolnij(baza);
    //printf("%s\n%s\n%s\n%s\n",argv[1],argv[2],argv[3],argv[4]);
    return 0;
}