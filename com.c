#include<stdio.h>
int main()
{
 int k=0, a, i, n, x;
 char var[50];
 for(i=0;i<50;i++)
 {
     scanf("%c", &var[i]);
     if(var[i]>=48&&var[i]<=57)
     {
         var[i] -= 48;
         n++;
     }
     else if((var[i]=getchar())==10)
        break;
 }
 for(i=0;i<n;i++)
     k += sizeof(var[i]);
 if(n%3==0)
     a=0;
     else if(n%3==1)
     a=2;
 else if(n%3==2)
     a=1;
 for(i=0;i<n;i++)
 {
     printf("%d", var[i]);
     x++;
     if((a+x)==n)
         break;
     if((a+x)%3 == 0)
         printf(",");
     }
return 0;
}
