#include <ft_malloc.h>
#include <string.h>//
#include <stdio.h>//

extern void	*calloc(size_t count, size_t size)
{
	size_t	total;
	void	*ptr;

#ifdef LIBFT_MALLOC_LOG
	dprintf(2, "calloc(%zu, %zu) -> ", count, size);
#endif
	total = count * size;
	if ((ptr = malloc(total)) == NULL)
		return (NULL);
	memset(ptr, '\0', total);
	return (ptr);
}
