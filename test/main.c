#include <malloc.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*s[10];

	for (int i = 0; i < 10; i++)
	{
		s[i] = malloc(16);
		memcpy(s[i], "0123456789012345", 16);
	}
	for (int i = 0; i < 10; i++)
		puts(s[i]);
	show_alloc_mem();
}
