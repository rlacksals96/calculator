#include<stdio.h>
void comma(int x, int y);
int main()
{
    int var;
    scanf("%d", &var);
    comma(var, 0);
    return 0;
}
void comma(int x, int y)
{
    if(x>0)
    {
        comma(x/10, y+1);
        printf("%d", x%10);
        if(y!=0)    
            if(y%3==0)
                printf(",");
    }
}
