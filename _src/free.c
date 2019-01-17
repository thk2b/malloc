#include <malloc.h>
#include <assert.h>

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

static inline void	write_boundary_tag(t_block *block) //TODO: macro me
{
	char	*boundary;

	boundary = ((char*)DATA(block) + block->size - sizeof(size_t));
	*(size_t*)boundary = block->size;
}

void				free(void *ptr)
{
	t_block		*block;
	t_fblock	*prev_fblock;
	t_area		*area;

	#ifdef MALLOC_LOG
	malloc_log_free(ptr);
	#endif
	if (ptr == NULL)
		return ;
	if ((block = find_block(ptr, &prev_fblock, &area)) == NULL)
	{
		error_ptr_was_not_allocated(ptr);
		return ;
	}
	block->free = 1;
	write_boundary_tag(block);
	assert(prev_fblock < (t_fblock*)block);
	free_list_insert_after(prev_fblock, (t_fblock*)block, area);
	#ifdef MALLOC_LOG
	malloc_log(block, "freed_block");
	#endif
}
