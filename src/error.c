#include <malloc.h>
#include <unistd.h>

void	*error_ptr_was_not_allocated(void *ptr)
{
	put_str(2, "ERROR: pointer ");
	put_hex(2, (size_t)ptr, 1);
	put_str(2, " was not allocated\n");
	return (NULL);
}
