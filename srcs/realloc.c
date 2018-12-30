#include <ft_malloc.h>
#include <string.h>//
#include <stdlib.h>
#include <stdio.h>

static void*	malloc_free_copy(t_block *block, size_t size)
{
	void	*ptr;

	if ((ptr = malloc(size)) == NULL)
		return (NULL);
	memcpy(ptr, B_DATA(block), MIN(size, block->size));
	free(B_DATA(block));
	return (ptr);
}

static int		next_is_free(t_block *block, t_area *area)
{
	void	*end;
	t_block	*next;

	end = A_CUR_END(area);
	next = B_NEXT(block);
	return ((void*)next < end && next->used == 0);
}

static int		block_is_last_of_area(t_block *block, t_area *area)
{
	t_block		*next;
	void		*end;

	end = A_CUR_END(area);
	next = B_NEXT(block);
	return ((void*)next >= end);

}

void			*realloc(void *ptr, size_t size)
{
	t_area			*area;
	t_block			*block;
	t_free_block	*prev_free_block;
	size_t			diff;

	if (ptr == NULL)
		return (malloc(size));
	if ((block = find_block(ptr, &area, &prev_free_block)) == NULL)
	{
		write(2, "ERROR: realloc: pointer was not allocated\n", 43);
		return (NULL);
	}
	if (size == block->size)
		return (ptr);
	if (size < block->size)
	{
		//split block
		return (ptr);
	}
	diff = size - block->size;
	if (next_is_free(block, area))
	{
		merge_blocks(block, B_NEXT(block), prev_free_block, area);
		return (ptr);
	}
	if (block_is_last_of_area(block, area) && A_CAN_FIT(area, size - block->size))
	{
		area->cur_size += size - block->size;
		block->size = size;
		return (ptr);
	}
	return (malloc_free_copy(block, size));
}

// void	*realloc(void *ptr, size_t size)
// {
// 	t_block	*block;
// 	t_block	*next;
// 	t_area	*area;
// 	void	*end;
// 	void	*new_ptr;
// 	size_t	prev_size;

// 	#ifdef LIBFT_MALLOC_LOG
// 		dprintf(2, "realloc(%p, %zu) -> ", ptr, size);
// 	#endif
// 	if (ptr == NULL)
// 	{
// 		return (malloc(size));
// 	}
// 	size = MAX(ALLIGN(size, 8), sizeof(t_free_block*) * 2);
// 	block = find_block(ptr, &area, NULL);
// 	if (block == NULL)
// 	{
// 		dprintf(2, "ERROR: realloc %p: pointer was not allocated\n", ptr);
// 		return (NULL);
// 	}
// 	prev_size = block->size;
// 	if (size == prev_size)
// 	{
// 		return (ptr);
// 	}
// 	end = A_CUR_END(area);
// 	next = B_NEXT(block);
// 	if ((void*)next > end && size >= prev_size && A_CAN_FIT(area, size - prev_size))
// 	{
// 		block->size = size;
// 		area->cur_size += (size - prev_size);
// 		return (B_DATA(block));
// 	}
// 	if ((new_ptr = malloc(size)) == NULL)
// 	{
// 		return (ptr);
// 	}
// 	memcpy(new_ptr, ptr, MIN(block->size, size));
// 	free(ptr);
// 	return (new_ptr);
// }
