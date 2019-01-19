#include <shared.h>
#include <assert.h>
#include <string.h>

static inline t_free_block	*do_coalesce(t_area *a, t_free_block *fb, size_t requested_size)
{
	size_t			total;
	t_free_block	*cur;
	void			*end;

	end = AREA__CUR_END(a);
	total = 0;
	cur = fb;
	while ((void*)cur < end && total < requested_size)
	{
		assert(cur->block.free);
		total += cur->block.size + sizeof(t_block);
		area__destroy_free_block(a, cur);
		cur = (t_free_block*)BLOCK__NEXT((t_block*)cur);
	}
	if ((void*)cur == end)
	{
		assert(AREA__CAN_FIT(a, requested_size - total));
		a->cur_size += requested_size - total;
	}
	fb->block.size += total;
	assert(total >= requested_size);
	return (fb);
}

static inline t_free_block	*do_coalesce_back(t_area *a, t_free_block *fb, size_t offset, size_t requested_size)
{
	t_free_block	*new_fb;

	assert(AREA__IS_IN_BOUNDS(a, (char*)fb - offset));
	new_fb = (t_free_block*)((char*)fb - offset);
	assert(new_fb->block.free);
	return (do_coalesce(a, new_fb, requested_size));
}

/*
**	Attempt to gather at least requested_size from free blocks surounding fb
**	The rightmost free block of the same list as fb is set in last_encountered_adjacent_fb
**	Returns the extended free block or NULL if not enough space could be gathered
**	When extending, free blocks are removed from their list and destroyed apropriately
**	The returned free block may be before fb in the case where there was free space before fb
**	If rhe resulting block exceeds requested_size, it is split
*/
t_free_block				*area__coalesce(t_area *a, t_free_block *fb, size_t requested_size, t_free_block **last_encountered_adjacent_fb)
{
	size_t			space_before;
	size_t			space_after;

	space_after = area__count_free_space_after(a, &fb->block, requested_size, last_encountered_adjacent_fb);
	space_before = 0;
	if (fb->block.size + space_after < requested_size)
		space_before = area__count_free_space_before(a, &fb->block, requested_size);
	if (space_before + fb->block.size + space_after < requested_size)
		return (NULL);
	if (space_before)
		fb = do_coalesce_back(a, fb, space_before, requested_size);
	fb = do_coalesce(a, fb, requested_size);
	// if (fb->block.size > requested_size)
		// area__split_free_block(a, fb, requested_size);
	return (fb);
	// return (area__coalesce(a, fb, space_before, requested_size));
}
