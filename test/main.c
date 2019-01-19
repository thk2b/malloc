#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LIM 10
#define FACTOR 10
#define D "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

static void	do_alloc(size_t size, size_t n)
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

static void	test_free(void)
{
	for (int i = 0; i < 10000; i++)
	{
		do_alloc(100, 3);
		do_alloc(1000, 3);
		do_alloc(10000, 3);
	}
	hexdump_mem();
	show_alloc_mem();
}

int main(void)
{
	test_free();
}
