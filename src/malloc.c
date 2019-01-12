#include <malloc.h>

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

extern void	*malloc(size_t size)
{
	return (NULL);
}
