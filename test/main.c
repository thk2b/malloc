#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LIM 10
#define FACTOR 10
#define D "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

int main(void)
{
	char *s = malloc(1000);
	memset(s, 'a', 1000);
	char *t = realloc(s, 10000);
	memset(t, 'a', 10000);
	hexdump_mem();
	show_alloc_mem();
}
