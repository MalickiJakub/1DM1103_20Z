#ifndef _BAZA_H
#define _BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _Student {
    char * imie;
    char * nazwisko;
    char * nr_albumu;
    char * email;

    struct _Student *nast;
    struct _Student *poprz;
} Student;

typedef struct _Przedmiot {
    char * kod;
    char * nazwa;
    char * sem;

    struct _Przedmiot *poprz;
    struct _Przedmiot *nast;
    } Przedmiot;

typedef struct _Ocena {
    char * nr_albumu;
    char * kod_przedmiotu;
    float ocena;
    char * komentarz;
    struct _Ocena *nast;
 } Ocena;


typedef struct _SBaza {
    int liczba_stud, liczba_przed, liczba_ocen;
    Student *lista_studentow; /* Głowa listy! */
    Przedmiot *lista_przedmiotow;
    Ocena *lista_ocen;
} SBaza;

SBaza * wczytaj_baze(char *nazwa_pliku);
void zapisz_baze(char *nazwa_pliku, SBaza * baza);
void listuj_studentow(SBaza *baza);
void zwolnij(SBaza *baza);
int ile_studentow(SBaza *baza);
int ile_przedmiotow(SBaza *baza);
int ile_ocen(SBaza *baza);
void dodajPrzedmiot(SBaza *baza, char*kodP, char*nazwaP, char*semP);
void dodajStudenta(SBaza *baza, char*kodP, char*nazwaP, char*semP, char *mail);
void dodajOcene(SBaza *baza,char  *a,char *b,float c,char *d);

void oceny_studenta(char *nrAlbumu, Ocena *baza);
void oceny_przedmiotu(char *kod, Ocena *baza);

void wypisz_rekurencyjnie_stud(Student *el);
void wypisz_rekurencyjnie_od_konca_stud(Student *el);
void wypisz_rekurencyjnie_przed(Przedmiot *el);

Student * ostatni(Student *glowa);
Student * sortuj_stud_od_konca(Student *glowa);

Przedmiot * ostatniPrzed(Przedmiot *glowa);
Przedmiot * sortuj_przed_nazwa(Przedmiot *glowa);
Przedmiot * sortuj_przed_kod(Przedmiot *glowa);
#endif