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

static inline void	*malloc_copy_free(t_block *block, size_t size)
{
	void	*new_ptr;

	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	memcpy(new_ptr, DATA(block), size);
	free(block);
	return (new_ptr);
}

void				*realloc(void *ptr, size_t size)
{
	t_block		*block;
	t_fblock	*prev_free_block;

	if (ptr == NULL)
		return (malloc(size));
	if ((block = find_block(ptr, &prev_free_block)) == NULL)
		return (error_ptr_was_not_allocated(ptr));
	if (block->size == size)
		return (ptr);
	if (block->size < size)
	{
		contract_block(block, size);
		return (DATA(block));
	}
	if (extend_block(block, size))
		return (DATA(block));
	return (malloc_copy_free(block, size));
}
