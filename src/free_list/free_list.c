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
**	Insert in address order
**	Invariant: For all fb of fl, fb->prev < fb < fb->next where < compares memory addresses
**	Inserting a new free block nfb requires finding a fb such that fb < nfb & fb->next > nfb
**	Search options:
**		v	Search entire free list							- O(n), easy implementation
**		x	Search area (backwards) and neighboring areas	- O(n), quick search when freeing adjacent blocks
**		>	Each area stores a pointer to the previous free block outside the area. This gives O(1) access to the first block of the area.
			When inserting, search linearly (back/forward based on position in block) through the block until a block of the right list is found. if not, then add based on the area's stored pointers.
			Fast because adjacent blocks are often freed together?

*/
static int			find_prev_free_block(t_area *area, t_free_block *fb, void *ctx)
{
	UNUSED(area);
	return ((void*)fb < ctx && (fb->next == NULL || ctx < (void*)fb->next));
}

static inline void	insert_address_ordered(t_free_list *fl, t_area *a, t_free_block *fb)
{
	t_area			*prev_block_area;
	t_free_block	*prev;
	t_free_block	*next;

	UNUSED(a);//FIXME: start search here
	prev = free_list__search(fl, &prev_block_area, find_prev_free_block, (void*)fb);
	next = prev ? prev->next : fl->head;
	assert((void*)prev < (void*)fb && ((void*)next == NULL || (void*)fb < (void*)next));
	if (prev == NULL)
		fl->head = fb;
	if (prev)
		prev->next = fb;
	fb->prev = prev;
	if (next)
		next->prev = fb;
	fb->next = next;
}

/*
**	Add a new free block to the free list
**	Options
**	x	FIFO			- O(1) insert, disordered list, reuse addresses based on free timing, bad locality
**	x	LIFO			- _
**	->	Address order	- O(n) insert, ordered list, reuse early addresses, smoothe out irregular freeing patterns
*/
void				free_list__insert(t_free_list *fl, t_area *a, t_free_block *fb)
{
	insert_address_ordered(fl, a, fb);
}

void				free_list__remove(t_free_list *fl, t_area *area, t_free_block *fb)
{
	t_free_block	*prev;
	t_free_block	*next;

	UNUSED(area);
	prev = fb->prev;
	next = fb->next;
	if (prev == NULL)
		fl->head = next;
	else
		prev->next = next;
	if (next)
		next->prev = prev;
	fb->next = NULL;//FIXME: remove
	fb->prev = NULL;
}
