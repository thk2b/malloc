#include <shared.h>
#include <assert.h>

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
/*
**	Add a new free block to the free list
**	Options
**	x	FIFO			- O(1) insert, disordered list, reuse addresses based on free timing, bad locality
**	x	LIFO			- _
**	->	Address order	- O(n) insert, ordered list, reuse early addresses, smoothe out irregular freeing patterns
*/
static int		find_prev_free_block(t_area *area, t_free_block *fb, void *ctx)
{
	UNUSED(area);
	return ((void*)fb < ctx && (fb->next == NULL || ctx < (void*)fb->next));
}

static inline void			insert_between(t_free_list *fl, t_free_block *prev, t_free_block *fb, t_free_block *next)
{
	assert(prev < fb && (next == NULL || fb < next));
	if (prev == NULL)
		fl->head = fb;
	else
		prev->next = fb;
	fb->prev = prev;
	if (next)
		next->prev = fb;
	fb->next = next;
	assert(fb != fb->next && fb != fb->prev);
	assert(fb->prev < fb && (fb->next == NULL || fb < fb->next));
}

static inline void			insert_free_node(t_free_list *fl, t_free_block *nearest_fb, t_free_block *fb)
{
	assert(nearest_fb != fb);
	if (nearest_fb == NULL)
		insert_between(fl, NULL, fb, NULL);
	else if (nearest_fb < fb)
		insert_between(fl, nearest_fb, fb, nearest_fb->next);
	else
		insert_between(fl, nearest_fb->prev, fb, nearest_fb);
}

static inline t_free_block	*nearest_free_block(t_free_list *fl, t_area *a, t_free_block *fb)
{
	t_free_block	*nearest_fb;
	t_area			*nearest_area_with_fb;

	assert(fl->id < FL__N_FREE_LISTS);
	if (AREA__HAS_FREE_BLOCK(a, fl->id))
	{
		nearest_fb = free_list__search_in_area(fl, a, find_prev_free_block, (void*)fb);
		if (nearest_fb == NULL)
			nearest_fb = a->first_free_block[fl->id];
		assert(nearest_fb);
		assert(nearest_fb == NULL || nearest_fb->prev != fb);
	}
	else
	{
		nearest_area_with_fb = area_list__search_around(a, area__find_has_free_block, (void*)&fl->id);
		assert(nearest_area_with_fb != a);
		if (nearest_area_with_fb == NULL)
			nearest_fb = NULL;
		else if (nearest_area_with_fb < a)
			nearest_fb = nearest_area_with_fb->last_free_block[fl->id];
		else
			nearest_fb = nearest_area_with_fb->first_free_block[fl->id];
		assert(nearest_fb == NULL || nearest_fb->prev != fb);
	}
	assert(nearest_fb == NULL || nearest_fb->prev != fb);
	return (nearest_fb);
}

void				free_list__insert_local_address_ordered(t_free_list *fl, t_area *a, t_free_block *fb)
{
	t_free_block	*nearest_fb;

	nearest_fb = nearest_free_block(fl, a, fb);
	insert_free_node(fl, nearest_fb, fb);
	if (fb < a->first_free_block[fl->id] || a->first_free_block[fl->id] == NULL)
		a->first_free_block[fl->id] = fb;
	if (fb > a->last_free_block[fl->id] || a->last_free_block[fl->id] == NULL)
		a->last_free_block[fl->id] = fb;
}
