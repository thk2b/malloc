#include <malloc.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char *p[10];
	p[0] = malloc(32);
	p[1] = malloc(1);
	free(p[0]);
	free(p[1]);
	show_alloc_mem();
	dump_mem();
}
