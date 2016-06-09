#include <stdio.h>
#include <string.h>

void multi(char sum[],char a1[], char a2[]);
void rev(char p[], int a);
int main(void)
{
	char a[10][100]={0};

	for(int i=0;i<2;i++)
		scanf("%s",a[i]);

	rev(a[0],strlen(a[0]));
	rev(a[1],strlen(a[1]));

	multi(a[2],a[0],a[1]);

	rev(a[2],strlen(a[2]));
	printf("%s\n",a[2]);
	return 0;
}

void multi(char sum[],char a1[], char a2[])
{
	int carry=0;
	int i,j,size1,size2;
	char a3;
		size1=strlen(a1);
		size2=strlen(a2);

	for(i=0;i<size2;i++){
		for(j=0;j<size1;j++){
			sum[j+i]+=((a1[j]-'0')*(a2[i]-'0')+carry)%10;
			if(sum[j+i]>9){
				sum[j+i]%=10;
				sum[j+i+1]++;
			}
			carry=((a1[j]-'0')*(a2[i]-'0')+carry)/10;
		}
	}
	if(carry)
		sum[j+i-1]=carry+'0';
	for(int i=0;i<strlen(sum);i++)
		sum[i]+='0';
}

void rev(char a[], int size)
{
	int tmp;

	for(int i=0;i<size/2;i++){
		tmp=a[i];
		a[i]=a[size-1-i];
		a[size-1-i]=tmp;
	}
}
