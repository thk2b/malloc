#include <malloc.h>
#include <string.h>

/*
**	Resizes the memory area pointed to by ptr to size.
**	If it is impossible, a new allocation is made, the data is copied and the pointer is freed.
**	Returns a memory area of size size.
**	==
**	find block such that block.data == ptr
**	if found
**		if can be extended
**			extend
**		else
**			malloc size
**			copy
**			free
**	else
**		error
*/

static inline void	*malloc_copy_free(void *ptr, size_t size)
{
	void	*new_ptr;

	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void				*realloc(void *ptr, size_t size)
{
	t_block		*block;
	t_fblock	*prev_free_block;
	t_area		*area;

	if (ptr == NULL)
		return (malloc(size));
	size = ALLIGN(size, 8);
	if ((block = find_block(ptr, &prev_free_block, &area)) == NULL || block->free)
		return (error_ptr_was_not_allocated(ptr));
	if (block->size == size)
		return (ptr);
	if (block->size > size)
	{
		split_block(block, size);
		return (DATA(block));
	}
	if (extend_block(block, size, prev_free_block, area)) //TODO: split block
		return (DATA(block));
	return (malloc_copy_free(ptr, size));
}
