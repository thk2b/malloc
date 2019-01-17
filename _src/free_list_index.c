#include <malloc.h>

size_t	free_list_index(size_t block_size)
{
	if (block_size >= 265)
		return (2);
	if (block_size >= 56)
		return (1);
	return (0);
}
