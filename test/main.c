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

// int main(void)
// {
// 	char *p[10];
// 	for (int i = 0; i < 10; i++)
// 	{
// 		p[i] = malloc(100);
// 		memcpy(p[i], D, 100);
// 	}
// 	dump_mem();
// 	for (int i = 0; i < 10; i++)
// 		if (i != 5 && i != 9)
// 			free(p[i]);
// 	dump_mem();
// 	realloc(p[5], 300);
// 	// realloc(p[5], 600);
// 	// realloc(p[5], 500);
// 	dump_mem();
// 	show_alloc_mem();
// }

// int main(void)
// {
// 	char *s = malloc(8160);
// 	s = realloc(s, 10000);
// 	(void)s;
// 	dump_mem();
// }
// int main(void)
// {
// 	char *s[10];
// 	char *t[10];
// 	char *u;

// 	for (int i = 0; i < 10; i++)
// 	{
// 		s[i] = malloc(240);
// 		t[i] = malloc(25);
// 		if (i == 5)
// 			u = malloc(240);
// 	}
// 	dump_mem();
// 	for (int i = 3; i < 10; i++)
// 	{
// 		free(s[i]);
// 		free(t[i]);
// 	}
// 	realloc(u, 1);
// 	dump_mem();
// 	show_alloc_mem();
// }

// int main(void)//realloc resize back
// {
// 	char *a = malloc(0);
// 	memcpy(a, D, MIN_BLOCK_SIZE);
// 	char *b = malloc(80);
// 	memcpy(b, D, 80);
// 	char *c = malloc(80);
// 	memcpy(c, D, 80);
// 	(void)c;
// 	free(a);
// 	free(b);
// 	dump_mem();
// 	char *d = malloc(88);

// 	memcpy(d, D, 80);
// 	c = realloc(c, 88);
// 	memcpy(c, D, 88);
// 	dump_mem();
// 	show_alloc_mem();
// 	(void)d;
// }

int main(void)//coalesce 3 blocks + wilderness
{
	char *a = malloc(10);
	char *b = malloc(10);
	char *c = malloc(10);
	malloc(10);
	malloc(10);
	free(a);
	free(b);
	free(c);
	char *d = malloc(40);
	(void)d;
	dump_mem();
	show_alloc_mem();
}
// int main(void)//coalesce 3 blocks + wilderness
// {
// 	char *a = malloc(10);
// 	char *b = malloc(10);
// 	char *c = malloc(10);
// 	free(b);
// 	free(c);
// 	char *d = malloc(40);
// 	(void)d;
// 	dump_mem();
// 	show_alloc_mem();
// }
