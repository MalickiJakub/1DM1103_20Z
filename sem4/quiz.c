#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char napis[]="Podstawy Programowania S4";
    int dlugosc = strlen(napis);
    printf("%s (%d)\n",napis,dlugosc);
    return 0;
}