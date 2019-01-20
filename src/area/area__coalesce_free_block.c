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
	if ((void*)cur == end && total < requested_size)
	{
		a->cur_size += requested_size - total;
		total = requested_size;
	}
	assert(total >= requested_size);
	fb->block.size = total - sizeof(t_block);
	#ifdef LOG
	free_block__log(fb, "coalessed");
	#endif
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

static inline int			should_coalesce(size_t reclaimed_size, size_t requested_size)
{
	return (reclaimed_size >= requested_size / 4);
}

/*
**	Attempt to gather at least requested_size from free blocks surounding fb
**	The rightmost free block of the same list as fb is set in last_encountered_adjacent_fb
**	Returns the extended free block or NULL if not enough space could be gathered
**	When extending, free blocks are removed from their list and destroyed apropriately
**	The returned free block may be before fb in the case where there was free space before fb
**	If rhe resulting block exceeds requested_size, it is split
**	The coalesced block is not added to a free list
*/
t_free_block				*area__coalesce_free_block(t_area *a, t_free_block *fb, size_t requested_size, t_free_block **last_encountered_adjacent_fb)
{
	size_t			space_before;
	size_t			space_after;
	size_t			total_size;

	space_after = area__count_free_space_after(a, &fb->block, requested_size, last_encountered_adjacent_fb);
	space_before = 0;
	total_size = space_after + sizeof(t_block) + fb->block.size; 
	if (total_size < requested_size)
		space_before = area__count_free_space_before(a, &fb->block, requested_size);
	total_size += space_before;
	if (total_size < requested_size)
		return (NULL);
	if (should_coalesce(space_before + space_after, requested_size) == 0)
		return (NULL);
	if (space_before)
		fb = do_coalesce_back(a, fb, space_before, requested_size);
	else
		fb = do_coalesce(a, fb, requested_size);
	if (fb->block.size > requested_size)
		area__split_free_block(a, fb, requested_size);
	return (fb);
}
