#include <stdio.h>
int main(void)
{
	char input[60];
	int len=0;
	char temp;

	printf("input");
	scanf("%s", input);

	while(input[len] != '\0')//숫자 길이 측정
		len++;

	for(i=0;i<len/2;i++){//순서 뒤집기
		temp=input[i];
		input[i]=voca[(len-i)-1];
		input[(len-i)-1]=temp;
	}

	printf("%s \n", input);
	return 0;
}

