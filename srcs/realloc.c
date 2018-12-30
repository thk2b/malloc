#include <ft_malloc.h>
#include <string.h>//
#include <stdlib.h>
#include <stdio.h>

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*next;
	t_area	*area;
	void	*end;
	void	*new_ptr;
	size_t	prev_size;

#ifdef LIBFT_MALLOC_LOG
	dprintf(2, "realloc(%p, %zu) -> ", ptr, size);
#endif
	if (ptr == NULL)
	{
		return (malloc(size));
	}
	size = MAX(ALLIGN(size, 8), sizeof(t_free_block*) * 2);
	block = find_block(ptr, &area, NULL);
	if (block == NULL)
	{
		dprintf(2, "ERROR: realloc %p: pointer was not allocated\n", ptr);
		return (NULL);
	}
	prev_size = block->size;
	if (size == prev_size)
	{
		return (ptr);
	}
	end = A_CUR_END(area);
	next = B_NEXT(block);
	if ((void*)next > end && size >= prev_size && A_CAN_FIT(area, size - prev_size))
	{
		block->size = size;
		area->cur_size += (size - prev_size);
		return (B_DATA(block));
	}
	if ((new_ptr = malloc(size)) == NULL)
	{
		return (ptr);
	}
	memcpy(new_ptr, ptr, MIN(block->size, size));
	free(ptr);
	return (new_ptr);
}
