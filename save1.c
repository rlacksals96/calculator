#include<stdio.h>
#include<string.h>
int main()
{
	FILE *save;
	int i,count=0;
	char x;
	char a[60],tmp[60] ,b[64], c[10];
	scanf("%[^\n]",b);
	if(b[2]=='=')  // 수식입력했을 때 = 이 있을 경우
	{
		if(count<11)  // 변수 최대 10개만 선언 할 수 있게
		{
			c[count]=b[0];
			for(i=4;i<64;i++)
				tmp[i-4]=b[i];  // = 뒤에 수를 다른 배열에 저장
			count++;
		}
	}
	save = fopen("save.out", "w+");
	fprintf(save, "%c = %s", c[0], tmp);
	fclose(save);
	return 0;
}
