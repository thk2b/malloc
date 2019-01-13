#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LIM 10
#define FACTOR 10
#define D "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define D1 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
int	main(void)
{
	char *p[LIM];
	for (int i = 0; i < LIM; i++)
		p[i] = malloc(i * FACTOR);
	for (int i = 0; i < LIM; i++)
		memcpy(p[i], D, ALLIGN(i * FACTOR, 8));
	dump_mem();
	show_alloc_mem();
	for (int i = 0; i < LIM; i++)
		free(p[i]);
	dump_mem();
	show_alloc_mem();
	for (int i = 0; i < LIM; i++)
		p[i] = malloc(i * FACTOR * 2);
	for (int i = 0; i < LIM; i++)
		memcpy(p[i], D1, ALLIGN(i * FACTOR * 2, 8));
	dump_mem();
	show_alloc_mem();
}
