#include <malloc.h>
#include <string.h>

/*
**	Allocates count * size bytes and initializes them to 0.
*/

void	*calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = size * count;
	if ((ptr = malloc(total)) == NULL)
		return (NULL);
	bzero(ptr, total);
	return (ptr);
}
