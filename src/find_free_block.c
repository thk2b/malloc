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
	t_block				*extended_block;
	t_fblock			*cur;
	t_fblock			*last_encountered;

	if((free_list = g_free_lists + free_list_index(size)) == NULL)
		return (NULL);
	cur = free_list->head;
	while (cur)
	{
		if (cur->block.free == 0)
			malloc_log(&cur->block, "not free but on free list");
		assert(cur->block.free == 1);
		if (cur->block.size >= size)
			return (cur);
		last_encountered = NULL;
		if ((extended_block = extend_block(&cur->block, size, &last_encountered, find_area_fblock(cur))))
			return ((t_fblock*)extended_block);
		cur = last_encountered ? last_encountered->next : cur->next;
	}
	return (NULL);
}
