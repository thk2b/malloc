#include <ft_malloc.h>
#include <stdio.h>
void	coalesce_block(t_block *block, t_area *area)
{
	t_block	*prev;
	t_block	*next;
	void	*end;
	end = A_CUR_END(area);

	next = B_NEXT(block);
	if ((void*)next < end && B_IS_FREE(next))
	{
		B_SET_SIZE(block, B_SIZE(block) + B_SIZE(next) + sizeof(t_block));
		next->prev = block->prev;
	}
	prev = B_PREV(block);
	if (prev && B_IS_FREE(prev))
	{
		B_SET_SIZE(prev, B_SIZE(prev) + B_SIZE(block) + sizeof(t_block));
		if ((void*)(next = B_NEXT(block)) < end && B_IS_USED(next))
			next->prev = prev;
	}
}

void	free(void *ptr)
{
	t_block	*block;
	t_area	*area;

	block = find_block(ptr, &area);
	if (block == NULL)
	{
		write(2, "ERROR: free: pointer was not allocated\n", 40);
		// dprintf(2, "ERROR: free: %p was not allocated\n", ptr);
		return ;
	}
	B_SET_FREE(block);
	coalesce_block(block, area);
}
