#include <stdio.h>
#include <string.h>

#define N 60

void add(char sm[], char a[], char b[]);
void wrt(char p[]);
void reverse(char arr[], int a);
int main(void)
{
	char a[N]={0};
	char b[N]={0};
	char sum[N]={0};

	gets(a);
	fflush(stdin);
	gets(b);
	fflush(stdin);
	add(sum, a, b);
	printf(" a = ");
	reverse(a,strlen(a));
    wrt(a);
	printf(" b = ");
	reverse(a,strlen(b));
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
		printf("%d", p[i]-'0');
	putchar('\n');
}
void reverse(char arr[], int a)
{
    int tmp;

     for(int i=0;i<a/2;i++)
       { 
	      tmp=arr[i];
		  arr[i]=arr[a-1-1];
		  arr[a-1-i]=tmp;
	   }

} 
