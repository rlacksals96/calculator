 #include<stdio.h>
 #include<stdlib.h>
 int main()
 {
     int i;
     char var[3][50] = {"123165165", "16515449", "51651651"};
     printf("1: clear, 2: var, 3: exit\n");
     scanf("%d", &i);
     switch(i)
     {
       case 1:
           system("clear");
           break;
       case 2:
           for(i=0;i<3;i++)
               printf("%c", var[i][50]);
           break;
       case 3:
           exit(1);
     }
   return 0;
}
