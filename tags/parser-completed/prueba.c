#include <stdio.h>

char *print();

int main(void)
{
	printf("%c\n", print()[0]);
	
	return 0;
}


char *print()
{
	char *t = (char *)malloc(10);
	
	t=strcpy(t, "Hola");
	
	return t;
}
