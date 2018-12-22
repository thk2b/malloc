#include <ft_malloc.h>
#include <string.h>

int main(void)
{
	char *p[3];
	int i;

	free(NULL);
	for (i = 0; i < 3; i++)
		p[i] = malloc(124);
	for (i = 0; i < 3; i++)
		free(p[i]);
	show_alloc_mem();
}

/*
#define NALLOCS 100
#define LEN 80

int main(void)
{
	char *s[NALLOCS];
	for (int j = 0; j < NALLOCS; j++)
	{
		s[j] = malloc(LEN);
		for (int i = 0; i < LEN; i++)
			s[j][i] = 'A';
	}
	for (int j = 0; j < NALLOCS; j++)
	{
		puts(s[j]);
	}
	show_alloc_mem();
}
*/
