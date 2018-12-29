#include <ft_malloc.h>
#include <string.h>//

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*next;
	t_area	*area;
	void	*end;
	void	*new_ptr;
	size_t	prev_size;

	if (!ptr)
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	size = ALLIGN(size, 8);
	block = find_block(ptr, &area);
	if (block == NULL)
	{
		write(2, "ERROR: realloc: pointer was not allocated\n", 40);
		return (NULL);
	}
	prev_size = B_SIZE(block);
	if (size <= prev_size)
		return (ptr);
	end = A_CUR_END(area);
	next = B_NEXT(block);
	if ((void*)next >= end && A_CAN_FIT(area, size - prev_size))
	{
		B_SET_SIZE(block, size);
		area->cur_size += (size - prev_size);
		return (B_DATA(block));
	}
	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	memcpy(new_ptr, ptr, B_SIZE(block));
	free(ptr);
	return (new_ptr);
}
