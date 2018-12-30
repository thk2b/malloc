#include <ft_malloc.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>

// void	test0(void)
// {
// 	char *s = malloc(10000);
// 	int i = 0;
// 	for (i = 0; i < 10000; i++)
// 		s[i] = 'B';
// 	puts(s);
// 	free(s);
// }

// void test1(void)
// {
// 	for (int i = 0; i < 100; i++)
// 	{
// 		test0();
// 	}
// 	show_alloc_mem();
// }

// void test2(void)
// {
// 	char *p1 = malloc(20);
// 	char *p2 = malloc(20);
// 	char *p3 = malloc(20);
// 	free(p1);
// 	show_alloc_mem();
// 	free(p2);
// 	show_alloc_mem();
// 	free(p3);
// 	show_alloc_mem();
// }

// void test3(void)
// {
// 	char *p1 = malloc(20);
// 	char *p2 = malloc(20);
// 	char *p3 = malloc(20);
// 	free(p3);
// 	show_alloc_mem();
// 	free(p2);
// 	show_alloc_mem();
// 	free(p1);
// 	show_alloc_mem();
// }

// void test4(void)
// {
// 	char *p1 = malloc(20);
// 	char *p2 = malloc(20);
// 	char *p3 = malloc(20);
// 	free(p2);
// 	show_alloc_mem();
// 	free(p3);
// 	show_alloc_mem();
// 	free(p1);
// 	show_alloc_mem();
// }

// void	test5(void)
// {
// 	char *p1 = malloc(1000);
// 	char *p2 = malloc(1000);
// 	(void)p2;
// 	strcpy(p1, "0123456789");
// 	puts(p1);
// 	p1 = realloc(p1, 1500);
// 	show_alloc_mem();
// 	puts(p1);
// 	strcpy(p1, "012345678901234");
// 	puts(p1);
// }

#define A "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"


void	test8(void)
{
	char *p[3][1000];
	for(int i = 0; i < 1000; i++){
		p[0][i] = malloc(1000);
		p[1][i] = malloc(100);
		p[2][i] = malloc(10);
		memcpy(p[0][i], A, 1000);
		p[0][i][999] = 0;
		memcpy(p[1][i], A, 100);
		memcpy(p[2][i], A, 10);
		// puts(p[0][i]);
		// puts(p[1][i]);
		// puts(p[2][i]);
	}
	// for(int i = 0; i < 1000; i++){
	// 	p[0][i] = realloc(p[0][i], 2000);
	// 	p[1][i] = realloc(p[1][i], 200);
	// 	p[2][i] = realloc(p[2][i], 20);
	// 	memcpy(p[0][i], A A, 2000);
	// 	p[0][i][1999] = 0;
	// 	memcpy(p[1][i], A A, 200);
	// 	memcpy(p[2][i], A A, 20);
	// 	puts(p[0][i]);
	// 	puts(p[1][i]);
	// 	puts(p[2][i]);
	// }
	// show_alloc_mem();
	for(int i = 0; i < 1000; i++){
		free(p[0][i]);
		free(p[1][i]);
		free(p[2][i]);
	}
	show_alloc_mem();
}

// // void	test7(void)
// // {
// // 	char *s = malloc(100);
// // 	char *t = realloc(s, 200);
// // 	memcpy(t, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 200);
// // 	free(t);
// // }

void	test6(void)
{
	char *p[3][1000];
	for(int i = 0; i < 1000; i++){
		p[0][i] = calloc(1, 1000);
		p[1][i] = calloc(1, 100);
		p[2][i] = calloc(1, 10);
		memcpy(p[0][i], A, 1000);
		memcpy(p[1][i], A, 100);
		memcpy(p[2][i], A, 10);
		// puts(p[0][i]);
		// puts(p[1][i]);
		// puts(p[2][i]);
	}
	for(int i = 0; i < 1000; i++){
		p[0][i] = realloc(p[0][i], 2000);
		p[1][i] = realloc(p[1][i], 200);
		p[2][i] = realloc(p[2][i], 20);
		memcpy(p[0][i], A A, 1999);
		memcpy(p[1][i], A A, 200);
		memcpy(p[2][i], A A, 20);
		puts(p[0][i]);
		puts(p[1][i]);
		puts(p[2][i]);
	}
	// show_alloc_mem();
	for(int i = 0; i < 1000; i++){
		free(p[0][i]);
		free(p[1][i]);
		free(p[2][i]);
	}
	show_alloc_mem();
}

void	test7(void)
{
	char *m[10];

	for (int i = 0; i < 10; i++)
	{
		m[i] = malloc(1000);
		memcpy(m[i], A, 1000);
	}
	free(m[5]);
	free(m[6]);
	show_alloc_mem();
	m[5] = malloc(100);
	show_alloc_mem();
}

int	main(void)
{
	test6();
	// char *s = malloc(100);
	// char *t = malloc(100);
	// s = realloc(s, 200);
	// s = realloc(s, 200);
	// show_alloc_mem();
	// free(t);
}
