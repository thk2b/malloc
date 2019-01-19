#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define D "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

void	do_alloc(size_t size, size_t n)
{
	char *s[n];

	for (size_t i = 0; i < n; i++)
	{
		s[i] = malloc(size);
		memset(s[i], 'a', size);
	}
	for (size_t i = 1; i < n; i += 2)
		free(s[i]);
	for (size_t i = 0; i < n; i += 2)
		free(s[i]);
}

void	test_free(void)
{
	for (int i = 0; i < 2; i++)
	{
		do_alloc(100, 3);
		do_alloc(1000, 3);
		do_alloc(10000, 3);
	}
	hexdump_mem();
	show_alloc_mem();
}

void	test_invalid_free(void)
{
	free(NULL);
	free((void*)11);
	free((void*)INT_MAX);
	free((void*)SIZE_T_MAX);
	free((void*)140236853095200);
}

void	test_simple_coalescing(void)
{
	char *s = malloc(104);
	memset(s, 'a', 104);
	char *t = malloc(104);
	memset(t, 'a', 104);
	free(t);
	free(s);
	char *u = malloc(208);
	memset(u, 'b', 208);
	hexdump_mem();
	show_alloc_mem();
}

void	test_coalescing_forward(void)
{
	char *s = malloc(104);
	memset(s, 'a', 104);
	char *t = malloc(104);
	memset(t, 'a', 104);
	char *u = malloc(104);
	memset(u, 'a', 104);
	char *v = malloc(104);
	memset(v, 'a', 104);
	free(t);
	free(u);
	free(s);
	s = malloc(240);
	memset(s, 'b', 240);
	hexdump_mem();
	show_alloc_mem();
}

void	test_coalescing_backward(void)
{
	char *s = malloc(0);
	char *t = malloc(256);
	memset(t, 'a', 256);
	malloc(0);
	free(s);
	free(t);
	s = malloc(264);
	memset(s, 'b', 264);
	hexdump_mem();
	show_alloc_mem();
}

int main(void)
{
	test_free();
}
