#include <errno.h>
#include <string.h>
#include <shared.h>

void	*error__no_mem(char *msg)
{
	put_str(2, "ERROR: ");
	put_str(2, msg);
	put_str(2, ": ");
	put_str(2, strerror(errno));
	put_str(2, "\n");
	return (NULL);
}

void	error__ptr_was_not_allocated(char *msg, void *ptr)
{
	put_str(2, "ERROR: ");
	put_str(2, msg);
	put_str(2, ": Pointer ");
	put_hex(2, (size_t)ptr, 1);
	put_str(2, " was not allocated\n");
}

#ifdef LOG
void	error__log_open_failed(void)
{
	put_str(2, "ERROR: couldn't open log file: ");
	put_str(2, strerror(errno));
	put_str(2, "\n");
}
#endif
