#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    /*printf("%s \n",argv[1]);
    tu po prostu testowałem czy dobrze podaję argumenty
    */
    float a=atof(argv[1]); 
   printf("wartość %f do kwadratu to %f \n",a,a*a);
    return(0);
}