#include <malloc.h>
#include <assert.h>

/*
**	first fit free list search (O(n))
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
	extern t_free_list	g_free_lists[];
	t_free_list			*free_list;
	t_fblock			*cur;

	if((free_list = g_free_lists + free_list_index(size)) == NULL)
		return (NULL);
	cur = free_list->head;
	while (cur)
	{
		assert(cur->block.free == 1);
		if (cur->block.size >= size)
			return (cur);
		cur = cur->next;
		// TODO: check for free neighbors
	}
	return (NULL);
}
