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

void	free(void *ptr)
{
	t_block	*block;

	if ((block = find_block(ptr)) == NULL)
		return ((void)error_ptr_was_not_allocated(ptr));
	block->free = 1;
	#ifdef MALLOC_LOG
	malloc_log_freed_block(block);
	#endif
}
