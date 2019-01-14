#include <malloc.h>

/*
**	Signals to the allocator that the memory pointed to by ptr can be reused.
**	The pointer must have been previously allocated by a call to malloc.
**	==
**	find block such that block.data == ptr
**	if found
**		mark as used
**		insert into apropriate free list
**	else
**		error
*/

static inline void		free_list_insert(t_fblock *prev, t_fblock *fblock)
{
	extern t_free_list	g_free_lists[];
	t_fblock			*next;

	if (prev == NULL)
	{
		fblock->prev = NULL;
		fblock->next = NULL;
		g_free_lists[free_list_index(fblock->block.size)].head = fblock;
		return ;
	}
	next = prev->next;
	prev->next = fblock;
	if (next)
		next->prev = fblock;
	fblock->next = next;
	fblock->prev = prev;
}

void					free(void *ptr)
{
	t_block		*block;
	t_fblock	*prev_fblock;

	if ((block = find_block(ptr, &prev_fblock)) == NULL)
	{
		error_ptr_was_not_allocated(ptr);
		return ;
	}
	block->free = 1;
	free_list_insert(prev_fblock, (t_fblock*)block);
	#ifdef MALLOC_LOG
	malloc_log_freed_block(block);
	#endif
}
