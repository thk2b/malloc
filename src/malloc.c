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
	t_area		*area;

	if (fblock->block.free == 0)
	{
		#ifdef MALLOC_LOG
		malloc_log((t_block*)fblock, "allocated free block");
		#endif
		return (DATA((t_block*)fblock));
	}
	fblock->block.free = 0;
	(void)size;
	area = find_area_fblock(fblock);
	free_list_remove(fblock, area);
	split_block(&fblock->block, size, area);
	#ifdef MALLOC_LOG
	malloc_log((t_block*)fblock, "allocated free block");
	#endif
	return (DATA((t_block*)fblock));
}

static inline void	*allocate_new_block(size_t size)
{
	t_area	*area;
	t_block	*block;
	size_t	total_block_size;

	total_block_size = size + sizeof(t_block);
	if ((area = find_area_with_available_size(total_block_size)) == NULL
	&& ((area = new_area(total_block_size)) == NULL))
		return (NULL);
	block = AREA_CUR_END(area);
	block->prev_free = 0;
	/* prev block is guaranteed to be used, if free it would have been extended */
	block->free = 0;
	block->size = size;
	area->cur_size += total_block_size;
	#ifdef MALLOC_LOG
	malloc_log(block, "new block");
	#endif
	return (DATA(block));
}

extern void			*malloc(size_t size)
{
	t_fblock	*fblock;

	size = MAX(ALLIGN(size, 8), MIN_BLOCK_SIZE);
	#ifdef MALLOC_LOG
	malloc_log_malloc(size);
	#endif
	if ((fblock = find_free_block(size)) == NULL)
		return (allocate_new_block(size));
	return (allocate_free_block(fblock, size));
}
