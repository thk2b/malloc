#include <malloc.h>
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

int	test0(void)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}

int	test1(void)
{
	int		i;
	char	*ptr;

	i = 0;
	while (i < 1024)
	{
		i++;
		ptr = malloc(1024);
		ptr[0] = 42;
	}
	return (0);
}

int	test2(void)
{
	int		i;
	char	*ptr;

	i = 0;
	while (i < 1024)
	{
		i++;
		ptr = malloc(1024);
		ptr[0] = 42;
		free(ptr);
	}
	return(0);
}

int	test3(void)
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = malloc(16 * M);
	p2 = malloc(16 * M);
	strcpy(p1, "Hello world\n");
	write(1, p1, strlen(p1));
	p3 = realloc(p1, 128 * M);
	for (int i = 0; i < 128 * M; i++)
		p3[i] = 'a';
	p3[127 * M] = 0;
//	write(1, p3, strlen(p3));
	return(0);
}

int test4(void)
{
	char *p;

	p = malloc(16);
	free(NULL);
	if (realloc(p + 5, 10) == NULL)
		write(1, "OK", 2);
	return (0);
}

int test5(void)
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	// hexdump_mem();
	return (0);
}

int	main(void)
{
	test5();
}
