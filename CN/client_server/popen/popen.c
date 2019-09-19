#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	FILE *f1,*f2; 
	char ch[10];
	f2 = popen("./p2.out","r");
	fscanf(f2,"%s",ch);
	printf("In parent\n");	
	write(1,ch,strlen(ch));
	printf("\n");
	pclose(f2);
	strcpy(ch,"HELLO");
	f1 = popen("./p3.out","w");
	fprintf(f1,"%s",ch);
	pclose(f1);
	return 0;
}
