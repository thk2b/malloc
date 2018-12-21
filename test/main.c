#include <ft_malloc.h>
#include <string.h>

int main(void)
{
	char *t = malloc(8);
	for (int j = 0; j < 10; j++)
	{
		char *s = malloc(8000);
		for (int i = 0; i < 8000; i++)
			s[i] = 'A';
	}
	strcpy(t, "1234567");
	// puts(s);
	puts(t);
	show_alloc_mem();
}
