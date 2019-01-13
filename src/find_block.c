#include <malloc.h>

/*
**	find an allocated block given its address
**	==
**	for each alocated area
**		if ptr is in range(area, area + area.size)
**			for each block
**				if block.data == ptr
**					return block
**	return nil
*/

static inline t_block	*find_block_in_area(t_area *area, void *ptr)
{
	t_block	*block;
	void	*area_cur_end;

	area_cur_end = AREA_CUR_END(area);
	block = AREA_HEAD(area);
	while ((void*)block < area_cur_end)
	{
		if (DATA(block) == ptr)
			return (block);
		block = BLOCK_NEXT(block);
	}
	return (NULL);
}

t_block					*find_block(void *ptr)
{
	extern t_area	*g_area_head;
	t_area			*area;

	area = g_area_head;
	while (area)
	{
		if (AREA_PTR_IS_IN_RANGE(area, ptr))
			return (find_block_in_area(area, ptr));
		area = area->next;
	}
	return (NULL);
}
