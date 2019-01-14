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

void					free(void *ptr)
{
	t_block		*block;
	t_fblock	*prev_fblock;
	t_area		*area;

	if ((block = find_block(ptr, &prev_fblock, &area)) == NULL)
	{
		error_ptr_was_not_allocated(ptr);
		return ;
	}
	block->free = 1;
	free_list_insert_after(prev_fblock, (t_fblock*)block);
	#ifdef MALLOC_LOG
	malloc_log_freed_block(block);
	#endif
}
