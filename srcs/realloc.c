#include <ft_malloc.h>
#include <string.h>

extern void	*realloc(void *ptr, size_t size)
{
	char	*new_ptr;
	t_block	*block;

	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	if (ptr == NULL)
		return (new_ptr);
	if ((block = find_block(ptr)) == NULL)
		return (new_ptr);
	memmove(new_ptr, ptr, MIN(block->size, size));
	free(ptr);
	return (new_ptr);
}
