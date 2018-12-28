#include <ft_malloc.h>

/*
**	initialize a new block
*/
void			new_block(t_block *block, size_t size, t_block *prev)
{
	B_SET_USED(block);
	B_SET_SIZE(block, size);
	block->prev = prev;
}

/*
**	add a block `b` after `a`
*/
void			append_block(t_block *a, t_block *b)
{
	b->prev = a;
}

static t_block	*find_free_block_in_area(t_area *area, size_t size)
{
	t_block	*prev_block;
	t_block	*block;
	t_block	*end;

	end = A_CUR_END(area);
	block = A_HEAD(area);
	prev_block = NULL;
	while (block < end)
	{
		if (B_IS_FREE(block) && B_SIZE(block) >= size)
		{
			area->cur_size += size;
			return (block);
		}
		prev_block = block;
		block = B_NEXT(block);
	}
	/*
	**	couldn't find an existing block large enpigh in area
	*/
	if (A_CAN_FIT(area, size + sizeof(t_block)))
	{
		block = prev_block ? B_NEXT(prev_block) : A_HEAD(area);
		new_block(block, size, prev_block);
		area->cur_size += size;
		append_block(prev_block, block);
		return (block);
	}
	/*
	**	area cannot fit requested block
	*/
	return (NULL);
}

t_block			*find_free_block(t_area *area, size_t size)
{
	t_area	*prev_area;
	t_block	*block;

	while (area)
	{
		if ((block = find_free_block_in_area(area, size)))
			return (block);
		prev_area = area;
		area = area->next;
	}
	/*
	**	couldn't find an area with enough space for the requested block
	*/
	if ((area = new_area(size)) == NULL)
		return (NULL);
	append_area(prev_area, area);
	block = A_HEAD(area);
	new_block(block, size, NULL);
	area->cur_size += size;
	append_block(NULL, block);
	return (block);
}
