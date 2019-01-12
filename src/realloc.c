#include <malloc.h>

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

void	*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	return (NULL);
}
