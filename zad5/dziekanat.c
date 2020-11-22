
#include "dziekanat.h"
int znajdz(char *szukany_nr, char nr_albumow[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_nr, nr_albumow[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_przedmioty(char nr_albumow[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;
    int i;

    for (i=0; i <n; i++) {
        if (znajdz(dane[i].kod_przed, nr_albumow, ile_znalazlem ) == -1) {
            strncpy(nr_albumow[ile_znalazlem], dane[i].kod_przed, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}


void najlepszy_przedmiot(student dane[100], int ile_rekordow) {
    char nr_albumow[100][10];
    int ile_studentow;
    float sumy_ocen[100]={0};
    int sumy_ects[100]={0};
    //float srednie[100]={0};
    int i;
    int pozycja;
    int najlepsza_pozycja;
    int najgorsza_pozycja;
    float najlepsza = 0.0f;
    float najgorsza = 5;

    ile_studentow = znajdz_przedmioty(nr_albumow, dane, ile_rekordow);

    for (i=0; i < ile_rekordow; i++) {
        pozycja = znajdz( dane[i].kod_przed, nr_albumow, ile_studentow );
        // if (pozycje >= 0)
        sumy_ocen[pozycja] += dane[i].ocena;
        sumy_ects[pozycja]++;
    }    

    //for (i=0;i<ile_studentow; i++) 
    //    printf("Student [%d]: %s - %f:%d - %f \n", i+1, nr_albumow[i], 
    //   sumy_ocen[i], sumy_ects[i], sumy_ocen[i] / sumy_ects[i]);

    for (i=0; i < ile_studentow; i++) {
        if (najlepsza < sumy_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    char nazwanajlepszegoprzedmiotu[254];
    for(int i=0;i<ile_rekordow;i++)
    {
        if(strcmp(nr_albumow[najlepsza_pozycja],dane[i].kod_przed)==0)
        {
            strcpy(nazwanajlepszegoprzedmiotu,dane[i].nazwa_przed);
        }
    }

    printf("Najlepsza srednia:  ");
    printf("%s - %s: %f \n", 
         nr_albumow[najlepsza_pozycja], nazwanajlepszegoprzedmiotu,
        sumy_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );


    for (i=0; i < ile_studentow; i++) {
        if (najgorsza > sumy_ocen[i] / sumy_ects[i]) {
            najgorsza = sumy_ocen[i] / sumy_ects[i];
            najgorsza_pozycja = i;
        }
    }

    char nazwanajgorszegoprzedmiotu[254];
    for(int i=0;i<ile_rekordow;i++)
    {
        if(strcmp(nr_albumow[najgorsza_pozycja],dane[i].kod_przed)==0)
        {
            strcpy(nazwanajgorszegoprzedmiotu,dane[i].nazwa_przed);
        }
    }

    printf("Najgorsza srednia:  ");
    printf("%s - %s: %f \n", 
         nr_albumow[najgorsza_pozycja], nazwanajgorszegoprzedmiotu,
        sumy_ocen[najgorsza_pozycja] / sumy_ects[najgorsza_pozycja]
    );

}

int znajdz_studentow(char nr_albumow[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;
    int i;

    for (i=0; i <n; i++) {
        if (znajdz(dane[i].nr_albumu, nr_albumow, ile_znalazlem ) == -1) {
            strncpy(nr_albumow[ile_znalazlem], dane[i].nr_albumu, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}


void najlepszy_student(student dane[100], int ile_rekordow) {
    char nr_albumow[100][10];
    int ile_studentow;
    float sumy_wazonych_ocen[100];
    int sumy_ects[100];
    //float srednie[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0.0f;

    ile_studentow = znajdz_studentow(nr_albumow, dane, ile_rekordow);

    for (i=0; i < ile_rekordow; i++) {
        pozycja = znajdz( dane[i].nr_albumu, nr_albumow, ile_studentow );
        // if (pozycje >= 0)
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }    

    /*for (i=0;i<ile_studentow; i++) 
        printf("Student [%d]: %s - %f:%d - %f \n", i+1, nr_albumow[i], 
        sumy_wazonych_ocen[i], sumy_ects[i], sumy_wazonych_ocen[i] / sumy_ects[i]); */

    for (i=0; i < ile_studentow; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepszy student: \n");
    printf("Student [%d] - %s %s: %s - %f \n", 
        najlepsza_pozycja+1,dane[najlepsza_pozycja].imie,dane[najlepsza_pozycja].nazwisko, nr_albumow[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );

}