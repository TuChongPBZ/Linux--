#include <stdio.h>







float sum_elements(float a[], unsigned length)
{
	printf("length:%lu\n", length);
	int i;
	float result = 0;
	for (i = 0; i <= length-1; i++)
	{
		result += a[i];
		printf("a[%d]:%f\n", i, a[i]);
	}
	printf("result:%f\n", result);
	return result;
}




int main(void)
{
	float a[] = {1.0, 2.0, 3.0, 4.0};
	printf("I'm father. pid:%d, father pid:%d, sizeof:%lu\n",getpid(), getppid(),sizeof(a));
	sum_elements(a, 0);
}
