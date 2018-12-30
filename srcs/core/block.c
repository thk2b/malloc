#include <ft_malloc.h>
#include <assert.h>

void			new_block(t_block *block, size_t size)
{
	block->used = 1;
	block->size = size;
}

/*
**	merges adjacent blocks a and b into one
**	a and b must be free, or a must be used and b must be free.
**	cannot merge a used block into a free one.
*/
void			merge_blocks(t_block *a, t_block *b, t_free_block *prev_free_block, t_area *area)
{
	t_free_block	*a_f;
	t_free_block	*b_f;

	assert(b->used == 0);
	a->size += b->size + sizeof(t_block);
	area->cur_size -= sizeof(t_block);
	b_f = (t_free_block*)b;
	if (a->used == 0)
	{
		a_f = (t_free_block*)a;
		a_f->next = b_f->next;
		if (b_f->next)
			b_f->next->prev = a_f;
	}
	else
	{
		if (prev_free_block)
			prev_free_block->next = b_f->next;
		if (b_f->next)
			b_f->next->prev = prev_free_block;
	}
}

static t_block	*find_free_block_in_area(t_area *area, size_t size)
{
	t_free_block	*cur_block;
	t_block			*block;

	cur_block = area->free_head;
	while (cur_block)
	{
		if (cur_block->used == 0 && cur_block->size >= size)
		{
			if (cur_block->prev)
				cur_block->prev->next = cur_block->next;
			if (cur_block->next)
				cur_block->next->prev = cur_block->prev;
			return ((t_block*)cur_block);
		}
		cur_block = cur_block->next;
	}
	if (!A_CAN_FIT(area, size + sizeof(t_block)))
		return (NULL);
	block = A_CUR_END(area);
	new_block(block, size);
	area->cur_size += sizeof(t_block) + size;
	return (block);
}

t_block			*find_free_block(t_area *area, size_t size)
{
	t_area	*prev_area;
	t_area	*cur_area;
	t_block	*block;

	prev_area = NULL;
	cur_area = area;
	while (cur_area)
	{
		if ((block = find_free_block_in_area(cur_area, size)))
		{
			block->used = 1;
			return (block);
		}
		prev_area = cur_area;
		cur_area = cur_area->next;
	}
	if ((cur_area = new_area(size)) == NULL)
		return (NULL);
	block = A_HEAD(cur_area);
	new_block(block, size);
	append_area(prev_area, cur_area);
	cur_area->cur_size += sizeof(t_block) + size;
	return (block);
}

t_block		*find_block_in_area(void *data_ptr, t_area *area, t_free_block **last_free_block)
{
	void	*end;
	t_block	*cur_block;

	end = A_END(area);
	cur_block = A_HEAD(area);
	*last_free_block = NULL;
	while ((void*)cur_block < end)
	{
		if (B_DATA(cur_block) == data_ptr)
			return (cur_block);
		if (cur_block->used == 0)
			*last_free_block = (t_free_block*)cur_block;
		cur_block = B_NEXT(cur_block);
	}
	return (NULL);
}

t_block		*find_block(void *data_ptr, t_area **area_ptr, t_free_block **last_free_block)
{
	extern t_zone	g_zones[];
	size_t			i;
	t_area			*cur_area;
	t_block			*block;

	*area_ptr = NULL;
	*last_free_block = NULL;
	i = 0;
	while (i < N_ZONES)
	{
		cur_area = g_zones[i].head;
		while (cur_area)
		{
			if ((block = find_block_in_area(data_ptr, cur_area, last_free_block)))
			{
				*area_ptr = cur_area;
				return (block);
			}
			cur_area = cur_area->next;
		}
		i++;
	}
	return (NULL);
}
