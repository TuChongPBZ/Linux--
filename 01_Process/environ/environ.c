#include <stdio.h>
#include <string.h>

#define TEST 0

extern char **environ;

char *my_getenv(char *name)
{
	int i;
	char *p;
	int len;
	for (i = 0; environ[i]; i++)
	{
		p = strstr(environ[i], "=");
		len = p - environ[i];
		if (strncmp(environ[i], name, len) == 0)
		{
			return p + 1;
		}
	}
	return NULL;
}




int main(int argc, char *argv[])
{
	int i;
	char *evrname;
	if (argc > 2) perror("argc > 2");
	
#if TEST
	for(i = 0; environ[i] != NULL; i++){
		printf("%s\n", environ[i]);
	}
#endif

	evrname = my_getenv(argv[1]);
	printf("evrname:%s\n", evrname);

	return 0;
}

