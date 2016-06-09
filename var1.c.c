#include <stdio.h>
#include<stdlib.h>
#include <string.h>
int main()
{
	char a[50],b[]={"Hello"};
	scanf("%[^\n]",a);
	getchar();
	if((strcmp(a,"var")==0)||(strcmp(a,"VAR"))==0)
	{
		if(b[0]!='\0')
			printf("b = %s",b);
	}
	else if((strcmp(a,"clear")==0)||(strcmp(a,"CLEAR"))==0)
		system("clear");
	else if((strcmp(a,"save")==0)||(strcmp(a,"SAVE"))==0)
	{ 
		save = fopen("save.out", "w+");
		fprintf(save, "%c", c[0]);
		fprintf(save, "%s", tmp);
		fclose(save);
	}
	else if((strcmp(a,"load")==0)||(strcmp(a,"LOAD"))==0)
	{
		save = fopen("save.out", "r+");
		fscanf(save, "%c", c[0]);
		fscanf(save, "%s", tmp);
		fclose(save);
	}
	else if((strcmp(a,"end")==0)||(strcmp(a,"END"))==0)
		exit(1);
      return 0;
  }
