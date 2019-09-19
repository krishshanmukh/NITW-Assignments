#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{

	char ch[10];
	scanf("%s",ch);
	write(1,ch,10);
	
	return 0;
}
