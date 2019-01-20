#include <assert.h>
#include <shared.h>

extern t_area_list	g_area_list;

t_free_list			*free_list__find(t_free_list *fls, size_t size)
{
	size_t		i;

	i = 1;
	while (i < FL__N_FREE_LISTS && fls[i].min_size <= size)
	{
		i++;
	}
	return (fls + (i - 1));
}

/*
**	Iterates through the free list
**	Return the first free block for which fn returns 1
**	Sets areap to the area in which the block is found.
*/
t_free_block	*free_list__search(t_free_list *fl, t_area **areap, t_free_list__search_fn fn, void *ctx)
{
	t_area			*area;
	t_free_block	*cur;
	void			*area_end;

	cur = fl->head;
	if (cur == NULL)
		return (NULL);
	area = area_list__search(&g_area_list, area__find_in_range, (void*)cur);
	assert(area);
	while (cur)
	{
		if (!AREA__IS_IN_BOUNDS(area, cur))
		{
			area = area_list__search_from(area, area__find_in_range, (void*)cur);
			assert(area);
			area_end = AREA__CUR_END(area);
		}
		if (fn(area, cur, ctx))
		{
			*areap = area;
			return (cur);
		}
		cur = cur->next;
	}
	*areap = NULL;
	return (NULL);
}
/*
**	Iterates through the free list
**	Return the first free block for which fn returns 1
**	If next is not NULL, continue the search from there
**	Sets areap to the area in which the block is found.
*/
t_free_block	*free_list__dynamic_search(t_free_list *fl, t_area **areap, t_free_list__dynamic_search_fn fn, void *ctx)
{
	t_area			*area;
	t_free_block	*cur;
	t_free_block	*next;
	void			*area_end;

	cur = fl->head;
	if (cur == NULL)
		return (NULL);
	area = area_list__search(&g_area_list, area__find_in_range, (void*)cur);
	assert(area);
	while (cur)
	{
		if (!AREA__IS_IN_BOUNDS(area, cur))
		{
			area = area_list__search_from(area, area__find_in_range, (void*)cur);
			assert(area);
			area_end = AREA__CUR_END(area);
		}
		next = NULL;
		if (fn(area, cur, &next, ctx))
		{
			*areap = area;
			return (next ? next : cur);
		}
		assert(next == NULL || next > cur);
		cur = next ? next : cur->next;
	}
	*areap = NULL;
	return (NULL);
}

t_free_block	*free_list__search_in_area(t_free_list *fl, t_area *a, t_free_list__search_fn fn, void *ctx)
{
	t_free_block	*b;
	t_free_block	*last;

	b = a->first_free_block[fl->id];
	last = a->last_free_block[fl->id];
	while (b && b <= last)
	{
		if (fn(a, b, ctx))
			return (b);
		b = b->next;
	}
	return (NULL);
}

void			free_list__insert(t_free_list *fl, t_area *a, t_free_block *fb)
{
	free_list__insert_address_ordered(fl, a, fb);
}

void				free_list__remove(t_free_list *fl, t_area *area, t_free_block *fb)
{
	t_free_block	*prev;
	t_free_block	*next;

	if (fb->block.free == 0)
		return ;
	if (fb == area->first_free_block[fl->id])
		area->first_free_block[fl->id] = AREA__IS_IN_BOUNDS(area, fb->next) ? fb->next : NULL;
	if (fb == area->last_free_block[fl->id])
		area->last_free_block[fl->id] = AREA__IS_IN_BOUNDS(area, fb->prev) ? fb->prev : NULL;
	prev = fb->prev;
	next = fb->next;
	if (prev == NULL)
		fl->head = next;
	else
		prev->next = next;
	if (next)
		next->prev = prev;
	fb->next = NULL;
	fb->prev = NULL;
}
