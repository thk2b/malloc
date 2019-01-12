#include <malloc.h>

/*
**	find a free block of size
**	==
**	find the appropriate free list
**	for each fblock of list
**		if fblock.size >= size
**			return fblock
**		else if coalesced size of fblock > size
**			do coalesce
**			return fblock
**	return nil
*/

t_fblock	*find_free_block(size_t size)
{
	(void)size;
	return (NULL);
}
