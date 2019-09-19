#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int main()
{

	char ch[10];
	scanf("%s",ch);
	printf("IN CHILD P3\n");
	write(1,ch,strlen(ch));
	printf("\n");
	return 0;
}
