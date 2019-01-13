#include <malloc.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*s[10];

	for (int i = 0; i < 10; i++)
	{
		s[i] = malloc(17);
		memcpy(s[i], "aaaaaaaaaaaaaaa", 16);
	}
	for (int i = 0; i < 10; i++)
		puts(s[i]);
	// s[0] = malloc(17);
	// s[0][0] = 127;
	// s[0][MIN_BLOCK_SIZE - 1] = 'A';
	// s[1] = malloc(17);
	// s[1][0] = 127;
	// s[1][MIN_BLOCK_SIZE - 1] = 'A';
	// malloc(1);
	show_alloc_mem();
	dump_mem();
}
