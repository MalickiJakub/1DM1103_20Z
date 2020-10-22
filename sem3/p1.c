#include<stdio.h>
int main(int argc, char argv[])
{
 for (int i=1; i<=100;i++){

 printf("%3d ",i);
 if (i==(23*3))
 printf("Nice ");
 if(i%10==0)
 printf("\n");
 }
}