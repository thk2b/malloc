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

// int main(void)//coalesce 3 blocks + wilderness
// {
// 	char *a = malloc(10);
// 	char *b = malloc(10);
// 	char *c = malloc(10);
// 	malloc(10);
// 	malloc(10);
// 	free(a);
// 	free(b);
// 	free(c);
// 	dump_mem();
// 	char *d = malloc(40);
// 	(void)d;
// 	dump_mem();
// 	show_alloc_mem();
// }

// int main(void)//coalesce 2 blocks + wilderness
// {
// 	char *a = malloc(10);
// 	(void)a;
// 	char *b = malloc(10);
// 	char *c = malloc(10);
// 	free(a);
// 	free(b);
// 	// free(c);
// 	dump_mem();
// 	char *d = malloc(100);
// 	(void)d;
// 	dump_mem();
// 	b = malloc(10);
// 	c = malloc(10);
// 	dump_mem();
// 	show_alloc_mem();
// }

// int main(void)
// {
// 	char *a = malloc(300);
// 	(void)a;
// 	char *b = malloc(300);
// 	char *c = malloc(300);
// 	char *d = malloc(300);
// 	char *e = malloc(300);
// 	(void)e;

// 	free(b);
// 	free(c);
// 	free(d);
// 	malloc(1500);
// 	dump_mem();
// 	show_alloc_mem();
// }

int main(void)
{
	for (int i = 0; i < 2; i++)
	{
		char *p = malloc(32);
		memcpy(p, D, 32);
	}
	for (int i = 0; i < 5; i++)
	{
		char * p = malloc(64);
		memcpy(p, D, 64);
	}
	for (int i = 0; i < 1; i++)
	{
		char *p = malloc(32);
		memcpy(p, D, 32);
	}
	for (int i = 0; i < 107; i++)
	{
		char *p = malloc(64);
		memcpy(p, D, 64);
	}
	char *p = realloc(NULL, 256);
	memcpy(p, D, 256);
	free(p);
	p = realloc(NULL, 256);
	memcpy(p, D, 256);
	p = realloc(p, 768);
	memcpy(p, D, ALLIGN(768, 8));

	// char *p = malloc(256);
	
	// p = realloc(p, 1024);
	// memcpy(p + 64, D, 1024 - 64);
	// free(p);
	// p = malloc(256);
	// memcpy(p, D, 256);
	// free(p);
	// char *p[10];
	// p[0] = malloc(64);
	// memcpy(p[0], D, 64);
	// p[1] = malloc(256);
	// memcpy(p[1], D, 256);
	// p[1] = realloc(p[1], 1024);
	// memcpy(p[1], D D, 1024);
	// free(p[1]);
	// p[2] = malloc(256);
	// memcpy(p[2], D, 256);
	// free(p[2]);
	dump_mem();
}
