#include <malloc.h>

/*
**	find a free block of size inside the free lists.
**	checks if adjacent free blocks can be merged.
**	return the block, or NULL if there is no free blocks available.
**	==
**	find the appropriate free list
**	for each free lists where list.min_size > size
**		for each fblock of list
**			if fblock.size >= size
**				return fblock
**			else if coalesced size of fblock > size
**				do coalesce
**				return fblock
**	return nil
*/

t_fblock	*find_free_block(size_t size)
{
	(void)size;
	return (NULL);
}
