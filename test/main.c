#include <ft_malloc.h>
#include <string.h>
#include <stdio.h>

void	test0(void)
{
	char *s = malloc(10000);
	int i = 0;
	for (i = 0; i < 10000; i++)
		s[i] = 'B';
	puts(s);
	free(s);
}

void test1(void)
{
	for (int i = 0; i < 100; i++)
	{
		test0();
	}
	show_alloc_mem();
}

void test2(void)
{
	char *p1 = malloc(20);
	char *p2 = malloc(20);
	char *p3 = malloc(20);
	free(p1);
	show_alloc_mem();
	free(p2);
	show_alloc_mem();
	free(p3);
	show_alloc_mem();
}

void test3(void)
{
	char *p1 = malloc(20);
	char *p2 = malloc(20);
	char *p3 = malloc(20);
	free(p3);
	show_alloc_mem();
	free(p2);
	show_alloc_mem();
	free(p1);
	show_alloc_mem();
}

void test4(void)
{
	char *p1 = malloc(20);
	char *p2 = malloc(20);
	char *p3 = malloc(20);
	free(p2);
	show_alloc_mem();
	free(p3);
	show_alloc_mem();
	free(p1);
	show_alloc_mem();
}

void	test5(void)
{
	char *p1 = malloc(1000);
	char *p2 = malloc(1000);
	(void)p2;
	strcpy(p1, "0123456789");
	puts(p1);
	p1 = realloc(p1, 1500);
	show_alloc_mem();
	puts(p1);
	strcpy(p1, "012345678901234");
	puts(p1);
}

int			main(void)
{
	setvbuf(stdout, NULL, 0, 0);
	(void)test2;
	(void)test3;
	(void)test4;
	(void)test1;
	test5();
}
