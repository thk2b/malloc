#include <assert.h>
#include <malloc.h>
#include <string.h>

/*
**	extend_block()
**		extend the allocated block so that it can fit size bytes
**		find all adjacent blocks that are free untill their combined size >= size
**		remove them from the list and create a new block
**		if the block is merged with previous ones, the data must be moved
**		return whether the block can be extended as such
**	lookahead(block, until)
**		count the size of all free blocks adjacent to block until the desired size is reached
**	coalesce(block, size)
**		merge all free blocks after block until block has been extended by at least size bytes.
**		remove them from the free lists
**			find the first and last free block of each list
**	==
**	
*/
static size_t	lookahead(t_block *block, size_t until, t_area *area)
{
	size_t	sum;
	t_block	*cur;
	void	*area_end;

	area_end = AREA_CUR_END(area);
	sum = 0;
	cur = BLOCK_NEXT(block);
	while ((void*)cur < area_end && cur->free && sum < until)
	{
		sum += cur->size + sizeof(t_block);
		cur = BLOCK_NEXT(cur);
	}
 	if (cur == area_end && AREA_CAN_FIT(area, until))
		return (until);
	return (sum);
}

// requires boundary blocks
// static size_t	lookback(t_block *block, size_t until, void *area_start)
// {
// 	size_t	sum;
// 	t_block	*cur;

// 	sum = 0;
// 	cur = BLOCK_PREV(block);
// 	while (cur >= area_start && cur->free && sum < until)
// 	{
// 		sum += cur->size + sizeof(t_block);
// 		cur = BLOCK_PREV(block);
// 	}
// 	return (sum);
// }

/*
**	coalesce
**		extend block by size bytes by removing all necesary free blocks ahead
*/
int				coalesce(t_block *block, size_t size, t_area *area)
{
	size_t		total;
	void		*area_end;
	t_block		*cur;
	t_block		*next;

	total = 0;
	cur = BLOCK_NEXT(block);
	area_end = AREA_CUR_END(area);
	while (total < size && (void*)cur < area_end)
	{
		next = BLOCK_NEXT(cur);
		assert(cur->free == 1);
		free_list_remove((t_fblock*)cur);
		total += sizeof(t_block) + cur->size;
		cur = next;
	}
	if (cur == area_end)
	{
		area->cur_size += size - total;
		total = size;
	}
	block->size += total;
	#ifdef MALLOC_LOG
	malloc_log_coalesced(block);
	#endif
	return (1);
}

int				extend_block(t_block *block, size_t size, t_fblock *last_free_block, t_area *area)
{
	size_t	size_ahead;
	size_t	extention_size;
	// size_t	size_behind;
	// size_t	total;

	(void)last_free_block;
	if (BLOCK_NEXT(block) == AREA_CUR_END(area) && AREA_CAN_FIT(area, size))
	{
		block->size += size;
		area->cur_size += size;
		#ifdef MALLOC_LOG
		malloc_log_extended_block(block);
		#endif
		return (1);
	}
	assert(size > block->size);
	extention_size = size - block->size;
	size_ahead = lookahead(block, extention_size, area);
	if (size_ahead >= extention_size)
		return (coalesce(block, size_ahead, area));
	return (0);
	// size_behind = lookback(block, size, AREA_HEAD(area));
	// if ((total = size_behind + size_ahead) < size)
	// 	return (0);
	// memmove(DATA((char*)block - size), DATA(block), size);
	// return (coalesce((char*)block + size, size));
}

/*
**	split_block(block, new_size)
**		resize block to newsize and create a free block immediately after it.
**		add the free block to the appropriate free list
*/
t_fblock	*split_block(t_block *block, size_t new_size)
{
	t_fblock	*fblock;
	size_t		fblock_size;

	assert(new_size < block->size);
	fblock_size = block->size - new_size;
	if (fblock_size < sizeof(t_block) + MIN_BLOCK_SIZE)
		return (NULL);
	block->size = new_size;
	fblock = (t_fblock*)BLOCK_NEXT(block);
	fblock->block.free = 1;
	fblock->block.size = fblock_size - sizeof(t_block);
	#ifdef MALLOC_LOG
	malloc_log_split_block(block);
	malloc_log_new_block(&fblock->block);
	#endif
	free_list_insert(fblock);
	return (fblock);
}
