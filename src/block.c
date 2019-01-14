#include <malloc.h>
#include <string.h>

/*
**	split block into two adjacent blocks of size `size` and `initial_size - size` bytes
**	the new block is free and added to the apropriate list
**	if `initial_size - size` < MIN_BLOCK_SIZE, the operation is not performed
**	returns whether the block was split
*/
int		split_block(t_block *block, size_t size, t_fblock *last_free_block)
{
	(void)block;
	(void)size;
	(void)last_free_block;
	return (0);
}

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
static size_t	lookahead(t_block *block, size_t until, void *area_end)
{
	size_t	sum;
	t_block	*cur;

	sum = 0;
	cur = BLOCK_NEXT(block);
	while ((void*)cur < area_end && cur->free && sum < until)
	{
		sum += cur->size + sizeof(t_block);
		cur = BLOCK_NEXT(cur);
	}
	if (cur == area_end)
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
*/
int				coalesce(t_block *block, size_t size)
{
	size_t		total;
	void		*limit;
	t_block		*cur;
	t_block		*next;

	total = 0;
	limit = (char*)block + size;
	cur = BLOCK_NEXT(block);
	while ((void*)cur < limit)
	{
		next = BLOCK_NEXT(cur);
		free_list_remove((t_fblock*)cur);
		cur = next;
	}
	block->size += size;
	#ifdef MALLOC_LOG
	malloc_log_coalesced(block);
	#endif
	return (1);
}

int				extend_block(t_block *block, size_t size, t_fblock *last_free_block, t_area *area)
{
	size_t	size_ahead;
	// size_t	size_behind;
	// size_t	total;

	(void)last_free_block;
	if (BLOCK_NEXT(block) == AREA_CUR_END(area) && AREA_CAN_FIT(area, size))
	{
		block->size += size;
		area->cur_size += size;
		return (1);
	}
	size_ahead = lookahead(block, size, AREA_CUR_END(area));
	if (size_ahead >= size)
		return (coalesce(block, size_ahead));
	return (0);
	// size_behind = lookback(block, size, AREA_HEAD(area));
	// if ((total = size_behind + size_ahead) < size)
	// 	return (0);
	// memmove(DATA((char*)block - size), DATA(block), size);
	// return (coalesce((char*)block + size, size));
}
