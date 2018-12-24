#include <ft_malloc.h>

void	free(void *ptr)
{
	t_block	*block;

	block = B_BLOCK(ptr);
	B_SET_FREE(block);
	//coalesce_block(block);
}
