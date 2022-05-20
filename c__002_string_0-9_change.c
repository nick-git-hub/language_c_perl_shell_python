#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 0
#define debug if (DEBUG) printf

int main()
{
	long val;
	char str[20];
	printf("[string 0~9 to number]\n");
	strcpy(str, "123456789");
	val = atol(str);		// 123456789
	printf("String value = %s, Long value = %ld\n", str, val);

	val = atol(&str[1]);	// 23456789
	printf("String value = %s, Long value = %ld\n", str, val);

	val = atol(&str[2]);	// 3456789
	printf("String value = %s, Long value = %ld\n", str, val);

	strcpy(str, "gitbook.net");
	val = atol(str);		// string , not change
	printf("String value = %s, Long value = %ld\n", str, val);

	return(0);
}
