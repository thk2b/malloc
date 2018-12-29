#include <ft_malloc.h>
#include <string.h>//
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
	if (size == 0)
	{
		size = 1;
	}
	if (ptr == NULL)
	{
		return (malloc(size));
	}
	size = ALLIGN(size, 8);
	block = find_block(ptr, &area);
	if (block == NULL)
	{
		dprintf(2, "ERROR: realloc %p: pointer was not allocated\n", ptr);
		return (NULL);
	}
	prev_size = B_SIZE(block);
	if (size <= prev_size)
	{
		return (ptr);
	}
	end = A_CUR_END(area);
	next = B_NEXT(block);
	if ((void*)next > end && A_CAN_FIT(area, size - prev_size))
	{
		B_SET_SIZE(block, size);
		area->cur_size += (size - prev_size);
		return (B_DATA(block));
	}
	if ((new_ptr = malloc(size)) == NULL)
	{
		return (NULL);
	}
	memcpy(new_ptr, ptr, MIN(B_SIZE(block), size));
	free(ptr);
	return (new_ptr);
}
