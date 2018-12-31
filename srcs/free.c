#include <ft_malloc.h>
#include <stdio.h>//
#include <assert.h>//

void		coalesce_block(t_block *block, t_area *area)
{
	(void)block;
	(void)area;
	return ;
}

void		new_free_block(t_block *block, t_free_block *last_free_block)
{
	t_free_block	*free_block;

	free_block = (t_free_block*)block;
	assert(free_block->used == block->used);
	assert(free_block->size == block->size);
	free_block->prev = last_free_block;
	free_block->next = NULL;
	if (last_free_block)
	{
		if (last_free_block->next)
			last_free_block->next->prev = free_block;
		free_block->next = last_free_block->next;
		last_free_block->next = free_block;
	}
}

extern void	free(void *ptr)
{
	t_block			*block;
	t_free_block	*last_free_block;
	t_area			*area;

	if (ptr == NULL)
		return ;
	area = NULL;
	last_free_block = NULL;
	block = find_block(ptr, &area, &last_free_block);
	if (block == NULL)
	{
		write(2, "ERROR: free: pointer was not allocated\n", 40);
		return ;
	}
	block->used = 0;
	new_free_block(block, last_free_block);
	if (area->free_head == NULL)
		area->free_head = (t_free_block*)block;
	coalesce_block(block, area);
}
