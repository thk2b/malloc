#include <malloc.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char *s = malloc(10000);
	for (int i = 0; i < 10000; i++)
		s[i] = 'a';
	char *t = malloc(10000);
	t[10000 - 1] = 'b';
	char *u = malloc(4529);
	u[4529 - 1] = 'c';
	free(t);
	show_alloc_mem();
	dump_mem();
}
