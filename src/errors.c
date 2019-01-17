#include <shared.h>

void	*error__no_mem(void)
{
	put_str(2, "ERROR: No memory\n");
	return (NULL);
}

void	error__pointer_was_not_allocated(void *ptr)
{
	put_str(2, "ERROR: Pointer ");
	put_hex(2, (size_t)ptr, 1);
	put_str(2, " was not allocated\n");
}
