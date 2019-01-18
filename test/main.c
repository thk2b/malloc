#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LIM 10
#define FACTOR 10
#define D "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

// int main(void)
// {
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		char *s = malloc(00);
// 		memset(s, 'a', 10);
// 		char *t = malloc(100);
// 		memset(t, 'a', 100);
// 		char *u = malloc(1000);
// 		memset(u, 'a', 1000);
// 		char *v = malloc(10000);
// 		memset(v, 'a', 10000);
// 	}
	// hexdump_mem();
	// show_alloc_mem();
// }

int main(void)
{
	char *s, *t;

	s = malloc(100);
	t = malloc(100);
	free(s);
	free(t);
	s = malloc(1000);
	t = malloc(1000);
	free(s);
	free(t);
	s = malloc(100);
	t = malloc(1000);
	hexdump_mem();
	show_alloc_mem();
}
