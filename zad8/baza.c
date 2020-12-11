#include "baza.h"

#define jezeli if

Student * wczytaj_studentow(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Student *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);
    Student *c;

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;
        stud->poprz = NULL;

        if (glowa == NULL)
            glowa = stud;
        else {
            c = ostatni(glowa);
            c->nast = stud;
            stud->poprz = c;
        }

        fgets(bufor, 254, fin);

        s = strtok(bufor, ";");
        stud->imie = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    return glowa;
}

Przedmiot * wczytaj_przedmioty(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Przedmiot *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);
    Przedmiot *c;

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;
        przed->poprz = NULL;

        if (glowa == NULL)
            glowa = przed;
        else {
            c = ostatniPrzed(glowa);
            c->nast = przed;
            przed->poprz = c;
        }

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        przed->kod = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->kod, s);

        s = strtok(NULL, ";");
        przed->nazwa = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->nazwa, s);

        s = strtok(NULL, "\n");
        przed->sem = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->sem, s);
    }

    return glowa;
}

Ocena * wczytaj_oceny(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Ocena *last_ocena = NULL;
    Ocena *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Ocena *oc = (Ocena*) malloc(sizeof(Ocena));
        oc->nast = NULL;

        if (last_ocena == NULL)
            glowa = oc;
        else
            last_ocena->nast = oc;
        last_ocena = oc;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        oc->kod_przedmiotu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->kod_przedmiotu, s);

        s = strtok(NULL, ";");
        oc->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->nr_albumu, s);

        s = strtok(NULL, ";");
        oc->ocena = atof(s);

        s = strtok(NULL, "\n");
        oc->komentarz = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->komentarz, s);
    }

    return glowa;
}

SBaza * wczytaj_baze(char *nazwa_pliku) {
    FILE *fin = fopen(nazwa_pliku, "r");
    if (fin == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza*) malloc( sizeof(SBaza) );
    baza->lista_studentow = wczytaj_studentow(fin);
    baza->lista_przedmiotow = wczytaj_przedmioty(fin);
    baza->lista_ocen = wczytaj_oceny(fin);
    fclose(fin);
    return baza;
}



void zapisz_studentow(SBaza * baza, FILE *fin)
{
    Student *n = baza->lista_studentow;
    fprintf(fin,"%d\n",ile_studentow(baza));
    while(n!=NULL)
    {
        fprintf(fin,"%s;%s;%s;%s\n",n->imie,n->nazwisko,n->nr_albumu,n->email);
        n=n->nast;
    }
}

void zapisz_przedmioty(SBaza * baza, FILE *fin)
{
    Przedmiot *n = baza->lista_przedmiotow;
    fprintf(fin,"%d\n",ile_przedmiotow(baza));
    while(n!=NULL)
    {
        fprintf(fin,"%s;%s;%s\n",n->kod,n->nazwa,n->sem);
        n=n->nast;
    }
}

void zapisz_oceny(SBaza *baza, FILE *fin)
{
    Ocena *n = baza->lista_ocen;
    fprintf(fin,"%d\n",ile_ocen(baza));
    while(n!=NULL)
    {
        fprintf(fin,"%s;%s;%f;%s\n",n->kod_przedmiotu,n->nr_albumu,n->ocena,n->komentarz);
        n=n->nast;
    }
}

void zapisz_baze(char *nazwa_pliku, SBaza * baza)
{
    FILE *fin = fopen(nazwa_pliku, "w");
    zapisz_studentow(baza, fin);
    zapisz_przedmioty(baza, fin);
    zapisz_oceny(baza, fin);
    fclose(fin);
}


int ile_studentow(SBaza *baza) {
    int n = 0;
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    baza->liczba_stud = n;
    return n;
}
int ile_przedmiotow(SBaza *baza) {
    int n = 0;
    Przedmiot * stud = baza->lista_przedmiotow;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    return n;
}
int ile_ocen(SBaza *baza) {
    int n = 0;
    Ocena * stud = baza->lista_ocen;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    return n;
}

void dodajPrzedmiot(SBaza *baza, char*kodP, char*nazwaP, char*semP)
{
    //    ./mydb add_course 1DM69420 "Szybkie samochody" 2020A
    Przedmiot *n = baza->lista_przedmiotow;
    Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
    przed->kod = (char*) malloc((1+strlen(kodP))*sizeof(char));
    strcpy(przed->kod,kodP);
    przed->nazwa = (char*) malloc((1+strlen(nazwaP))*sizeof(char));
    strcpy(przed->nazwa, nazwaP);
    przed->sem = (char*) malloc((1+strlen(semP))*sizeof(char));
    strcpy(przed->sem, semP);
    //przed->nast = (Przedmiot*) malloc(sizeof(Przedmiot));
    przed->nast = n;
    baza->lista_przedmiotow = przed;
}

void dodajStudenta(SBaza *baza, char *kodP, char *nazwaP, char *semP, char *mail)
{
    Student *n = baza->lista_studentow;
    Student *stud = (Student*) malloc(sizeof(Student));
    stud->imie = (char*) malloc((1+strlen(kodP))*sizeof(char));
    strcpy(stud->imie, kodP);
    stud->nazwisko = (char*) malloc((1+strlen(nazwaP))*sizeof(char));
    strcpy(stud->nazwisko, nazwaP);
    stud->nr_albumu = (char*) malloc((1+strlen(semP))*sizeof(char));
    strcpy(stud->nr_albumu, semP);
    stud->email = (char*) malloc((1+strlen(mail))*sizeof(char));
    strcpy(stud->email, mail);
    //stud->nast = (Student*) malloc(sizeof(Student));
    stud->nast = n;
    baza->lista_studentow = stud;
}

void dodajOcene(SBaza *baza,char  *a,char *b,float c,char *d)
{
    Ocena *n = baza->lista_ocen;
    Ocena *stud = (Ocena*) malloc(sizeof(Ocena));
    stud->nr_albumu = (char*) malloc((1+strlen(a))*sizeof(char));
    strcpy(stud->nr_albumu, a);
    stud->kod_przedmiotu = (char*) malloc((1+strlen(b))*sizeof(char));
    strcpy(stud->kod_przedmiotu, b);
    stud->ocena = c;
    stud->komentarz = (char*) malloc((1+strlen(d))*sizeof(char));
    strcpy(stud->komentarz, d);
    //stud->nast = (Ocena*) malloc(sizeof(Ocena));
    stud->nast = n;
    baza->lista_ocen = stud;
}

void listuj_studentow(SBaza *baza) {
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

void zwolnij_student(Student *s) {
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    //free(s->nast);
    free(s);
}

void zwolnij_przedmiot(Przedmiot *s) {
    free(s->kod);
    free(s->nazwa);
    free(s->sem);
    //free(s->nast);
    free(s);
}

void zwolnij_ocena(Ocena *s) {
    free(s->nr_albumu);
    free(s->kod_przedmiotu);
    free(s->komentarz);
    //free(s->nast);
    free(s);
}

void zwolnij_liste_studentow(Student *s) {
    Student *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij_liste_przedmiotow(Przedmiot *s) {
    Przedmiot *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_przedmiot(s);
        s = n;
    }
}

void zwolnij_liste_ocen(Ocena *s) {
    Ocena *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_ocena(s);
        s = n;
    }
}

void zwolnij(SBaza *baza) {
    zwolnij_liste_studentow(baza->lista_studentow);
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    zwolnij_liste_ocen(baza->lista_ocen);
    free(baza);
}

void wypisz_rekurencyjnie_stud(Student *el) {
    if (el != NULL) {
        printf("%s %s %s %s\n", el->imie, el->nazwisko, el->nr_albumu, el->email);        
        wypisz_rekurencyjnie_stud( el->nast );
    }
}
void wypisz_rekurencyjnie_od_konca_stud(Student *el) {
    if (el != NULL) {
        wypisz_rekurencyjnie_od_konca_stud( el->nast );
        printf("%s %s %s %s\n", el->imie, el->nazwisko, el->nr_albumu, el->email);        
        
    }
}
void wypisz_rekurencyjnie_przed(Przedmiot *el) {
    if (el != NULL) {
        printf("%s %s %s\n", el->kod, el->nazwa, el->sem);        
        wypisz_rekurencyjnie_przed( el->nast );
    }
}
void wypisz_rekurencyjnie_oc(Ocena *el) {
    if (el != NULL) {
        printf("%s %s %f %s\n", el->kod_przedmiotu, el->nr_albumu, el->ocena, el->komentarz);        
        wypisz_rekurencyjnie_oc( el->nast );
    }
}

void wypisz_oc(Ocena *el)
{
    printf("%s %s %f %s\n", el->kod_przedmiotu, el->nr_albumu, el->ocena, el->komentarz);
}

void oceny_studenta(char *nrAlbumu, Ocena *baza)
{
    if(baza!=NULL)
    {
        if(strcmp(nrAlbumu,baza->nr_albumu)==0)
        {
            wypisz_oc(baza);
        }
        oceny_studenta(nrAlbumu, baza->nast);
    }
}

void oceny_przedmiotu(char *kod, Ocena *baza)
{
    if(baza!=NULL)
    {
        if(strcmp(kod,baza->kod_przedmiotu)==0)
        {
            wypisz_oc(baza);
        }
        oceny_przedmiotu(kod, baza->nast);
    }
}



// Część Szmurła

Student * ostatni(Student *glowa) {
    Student *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Student * usun(Student *glowa, Student *el) {
    Student *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;

                break;
            }

            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Student * najwiekszy(Student *el) {
    Student * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->nazwisko, max->nazwisko) > 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}

Student * sortuj_stud_od_konca(Student *glowa) {
    Student * nglowa = NULL;
    Student * m;
    Student * o; // = NULL;

    while (glowa != NULL) {
        m = najwiekszy(glowa);
        glowa = usun(glowa, m);
        
        o = ostatni(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
        // o = m;

        // printf("Najwiekszy: %s\n", m->nazwisko);
        // wypisz_rekurencyjnie(glowa);
    }

    return nglowa;
}

Student * zwroc(Student *glowa, int i) {
    while (glowa != NULL && i-- > 0) // i jest zmniejszany postfixowo - czyli po porownaniu z 0
        glowa = glowa->nast;    
    
    return glowa;
}





Przedmiot * ostatniPrzed(Przedmiot *glowa) {
    Przedmiot *el = glowa;
    if (el != NULL) {
        while (el->nast != NULL)
            el = el->nast;

        return el;
    } else
        return NULL;
}

Przedmiot * usunPrzed(Przedmiot *glowa, Przedmiot *el) {
    Przedmiot *c = glowa;
    if (glowa == el) {
        glowa = glowa->nast;
    } else {
        while (c != NULL) {
            if (c == el) {
                c->poprz->nast = c->nast;
                if (c->nast != NULL)
                    c->nast->poprz = c->poprz;

                break;
            }

            c = c->nast;
        }
    }
    c->nast = NULL;
    c->poprz = NULL;
    return glowa;
}

Przedmiot * najmniejszyPrzedNazwa(Przedmiot *el) {
    Przedmiot * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->nazwa, max->nazwa) < 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}

Przedmiot * sortuj_przed_nazwa(Przedmiot *glowa) {
    Przedmiot * nglowa = NULL;
    Przedmiot * m;
    Przedmiot * o; // = NULL;

    while (glowa != NULL) {
        m = najmniejszyPrzedNazwa(glowa);
        glowa = usunPrzed(glowa, m);
        
        o = ostatniPrzed(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
        // o = m;

        // printf("Najwiekszy: %s\n", m->nazwisko);
        // wypisz_rekurencyjnie(glowa);
    }

    return nglowa;
}

Przedmiot * zwrocPrzedNazwa(Przedmiot *glowa, int i) {
    while (glowa != NULL && i-- > 0) // i jest zmniejszany postfixowo - czyli po porownaniu z 0
        glowa = glowa->nast;    
    
    return glowa;
}

Przedmiot * najmniejszyPrzedKod(Przedmiot *el) {
    Przedmiot * max = NULL;
    while (el != NULL) {
        if (max == NULL) {
            max = el;
        } else {
            if ( strcmp(el->kod, max->kod) < 0 ) 
                max = el;
        }
        el = el->nast;
    }
    return max;
}


Przedmiot * sortuj_przed_kod(Przedmiot *glowa) {
    Przedmiot * nglowa = NULL;
    Przedmiot * m;
    Przedmiot * o; // = NULL;

    while (glowa != NULL) {
        m = najmniejszyPrzedKod(glowa);
        glowa = usunPrzed(glowa, m);
        
        o = ostatniPrzed(nglowa);
        if (o == NULL) {
            nglowa = m;
        } else {
            o->nast = m;
            m->poprz = o;
        }
        // o = m;

        // printf("Najwiekszy: %s\n", m->nazwisko);
        // wypisz_rekurencyjnie(glowa);
    }

    return nglowa;
}

