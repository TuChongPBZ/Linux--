#include <stdio.h>
#include <string.h>


int sprintf_test(char *a, char *b, int n)
{
	strncpy(a, b, n);
}
int main (void)
{
	char a[] = "pbzpbz1";
	char b[32] = {0};
	printf("a:%s, b:%s, sizeof:%u\n", a, b, sizeof(a));
	sprintf_test(b, a, sizeof(a));
	printf("a:%s, b:%s\n", a, b);
}
