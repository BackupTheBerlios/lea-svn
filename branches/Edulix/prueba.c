#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char *mystring=malloc(200);
	while(fscanf(stdin, "%s", mystring))
	{
		printf("%s\n", mystring);
	}
	return 0;
}
