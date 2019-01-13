#include <malloc.h>
#include <assert.h>

/*
**	Allocate max(allign(size, 8), min_block_size) bytes on the heap.
**	Return pointer to the allocated memory.
**	==
**	find a free block such that size <= block.size, try coalescing neighbors (O(n))
**	if found
**		mark as used
**		if block.size - size > split_threshold
**			split block
**			insert into appropriate free list (O(n))
**	else
**		allocate a new area
*/
static inline void	*allocate_free_block(t_fblock *fblock, size_t size)
{
	fblock->block.free = 0;
	fblock->block.size = size; // TODO: split
	return (DATA(&fblock->block));
}

static inline void	*allocate_new_block(size_t size)
{
	t_area	*area;
	t_block	*block;

	if ((area = find_area_with_available_size(size)) == NULL
	&& ((area = new_area(size)) == NULL))
		return (NULL);
	block = (t_block*)((char*)area + area->cur_size);
	block->free = 0;
	block->size = size;
	#ifdef MALLOC_LOG
	malloc_log_new_block(block);
	#endif
	area->cur_size += size + sizeof(t_block);
	assert(area->cur_size < area->size);
	return (DATA(block));
}

extern void			*malloc(size_t size)
{
	t_fblock	*fblock;

	size = MAX(ALLIGN(size, 8), MIN_BLOCK_SIZE);
	if ((fblock = find_free_block(size)) == NULL)
		return (allocate_new_block(size));
	return (allocate_free_block(fblock, size));
}
