#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LIM 10
#define FACTOR 10
#define D "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define D1 "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
// int	main(void)
// {
// 	char *p[LIM];
// 	for (int i = 0; i < LIM; i++)
// 		p[i] = malloc(i * FACTOR);
// 	for (int i = 0; i < LIM; i++)
// 		memcpy(p[i], D, ALLIGN(i * FACTOR, 8));
// 	dump_mem();
// 	show_alloc_mem();
// 	for (int i = 0; i < LIM; i++)
// 		free(p[i]);
// 	dump_mem();
// 	show_alloc_mem();
// 	for (int i = 0; i < LIM; i++)
// 		p[i] = malloc(i * FACTOR * 2);
// 	for (int i = 0; i < LIM; i++)
// 		memcpy(p[i], D1, ALLIGN(i * FACTOR * 2, 8));
// 	dump_mem();
// 	show_alloc_mem();
// }

// int main(void)
// {
// 	char *s = malloc(3000);
// 	memcpy(s, D D D D D D D D D D D D D D , 3000);
// 	free(s);
// 	char *t = malloc(2000);
// 	(void)t;
// 	dump_mem();
// }

// int main(void)
// //stress test
// {
// 	char *p[10000];
// 	for (int j = 0; j < 10000; j++)
// 	{
// 		p[j] = malloc(10000);
// 		memcpy(p[j], D, 100);
// 		memcpy(p[j] + 10000 - 100, D, 100);
// 	}
// 	// dump_mem();
// 	show_alloc_mem();
// }

int main(void)
{
	char *p[10];
	for (int i = 0; i < 10; i++)
	{
		p[i] = malloc(100);
		memcpy(p[i], D, 100);
	}
	for (int i = 0; i < 10; i++)
		if (i != 5)
			free(p[i]);
	dump_mem();
	realloc(p[5], 300);
	// realloc(p[5], 500);
	dump_mem();
}
