#include <stdio.h>

#define N 20

void add(char sm[], char a[], char b[]);
void wrt(char p[]);

int main(void)
{
	char a[N];
	char b[N];
	char sum[N];

	gets(a);
	fflush(stdin);
	gets(b);
	fflush(stdin);
	add(sum, a, b);
	printf(" a= ");
    wrt(a);
	printf(" b= ");
	wrt(b);
	printf(" sum= ");
	wrt(sum);
	return 0;
}
void add(char sum[], char a[], char b[])
{
	int carry = 0;
	int i;

	for (i=0;i<N;++i)
	{  
		sum[i]=(a[i]+b[i]+carry)%10;
		carry=(a[i]+b[i]+carry)/10;
	}
}
void wrt (char p[])
{
	int i;

	for (i = N-1; i>=1; --i)
		if (p[i]) break;
	for ( ; i>= 0; --i)
		printf("%d", p[i]);
	putchar('\n');
}
