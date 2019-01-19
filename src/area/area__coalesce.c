#include <shared.h>
#include <string.h>


/*
**	Attempt to gather at least requested_size from free blocks surounding fb
**	The rightmost free block of the same list as fb is set in last_encountered_adjacent_fb
**	Returns the extended free block or NULL if not enough space could be gathered
**	When extending, free blocks are removed from their list and destroyed apropriately
**	The returned free block may be before fb in the case where there was free space before fb
**	If rhe resulting block exceeds requested_size, it is split
*/
t_free_block	*area__coalesce(t_area *a, t_free_block *fb, size_t requested_size, t_free_block **last_encountered_adjacent_fb)
{
	size_t			space_before;
	size_t			space_after;
	t_free_list		*fl;

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
