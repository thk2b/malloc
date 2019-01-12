#include <malloc.h>

/*
**	Signals to the allocator that the memory pointed to by ptr can be reused.
**	The pointer must have been previously allocated by a call to malloc.
**	==
**	find block such that block.data == ptr
**	if found
**		mark as used
**	else
**		error
*/

void	free(void *ptr)
{
	(void)ptr;
}
