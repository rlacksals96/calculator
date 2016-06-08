#include<stdio.h>
#include<string.h>
int main()
{
	int cc = 0;
	int k=0, a, i, n, x, count;
	char var[50];
	scanf("%s", &var);
	for(i=0;i<50;i++)
	{
		if(var[i]>=48&&var[i]<=57)
			n++;
	}
	n-=1;
	k = strlen(var);
	if(n!=k)
	{
		for(i=0;i<k;i++)
		{
			if(var[i]=='.')
			{
				n = i;
				break;
			}
		}
	}
	if(n%3==0)
		a=0;
	else if(n%3==1)
		a=2;
	else if(n%3==2)
		a=1;
	for(i=0;i<k;i++)
	{
		if(var[i]=='.')
		{
			printf(".");
			a=0;
			x=0;
		}
		else
		{
			printf("%c", var[i]);
			x++;
			if((a+x)%3 == 0)
			{
					if(var[i+1]=='.')
						continue;
					else if(x==k||i==k-1)
						break;
					else
						printf(",");
			}
		}
	}
	return 0;
}
