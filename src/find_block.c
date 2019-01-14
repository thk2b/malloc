#include <malloc.h>

/*
**	find an allocated block given its address
**	also find the nearest free block to this block
**	==
**	for each alocated area
**		if ptr is in range(area, area + area.size)
**			for each block
**				if block.data == ptr
**					return block
**	return nil
*/

static inline t_block	*find_block_in_area(t_area *area, void *ptr, t_fblock **local_prev_fblock, t_fblock **prev_fblock)
{
	t_block		*block;
	void		*area_cur_end;

	area_cur_end = AREA_CUR_END(area);
	block = AREA_HEAD(area);
	while ((void*)block < area_cur_end)
	{
		if (block->free)
			local_prev_fblock[free_list_index(block->size)] = (t_fblock*)block;
		if (DATA(block) == ptr)
		{
			*prev_fblock = local_prev_fblock[free_list_index(block->size)];
			return (block);
		}
		block = BLOCK_NEXT(block);
	}
	return (NULL);
}

static inline void		init_prev_fblocks(t_fblock **fblocks)
{
	extern t_free_list	g_free_lists[];

	fblocks[0] = g_free_lists[0].head;
	fblocks[1] = g_free_lists[1].head;
	fblocks[2] = g_free_lists[2].head;
}

/*
**	find the block given its addres
**	find the nearest previous free list node
**		since we don't know the block size, keep track of the last element of every free list
*/
t_block					*find_block(void *ptr, t_fblock **prev_fblock, t_area **areap)
{
	extern t_area	*g_area_head;//FIXME: start from the end?
	t_area			*area;
	t_fblock		*local_prev_fblock[N_FREE_LISTS] = {0};

	init_prev_fblocks(local_prev_fblock);
	area = g_area_head;
	while (area)
	{
		if (AREA_PTR_IS_IN_RANGE(area, ptr))
		{
			*areap = area;
			return (find_block_in_area(area, ptr, local_prev_fblock, prev_fblock));
		}
		area = area->next;
	}
	*prev_fblock = NULL;
	*areap = NULL;
	return (NULL);
}
