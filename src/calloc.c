#include <malloc.h>
#include <shared.h>
#include <string.h>
#include <libft.h>

void	*calloc(size_t count, size_t size)
{
	void	*addr;
	size_t	total;

	total = size * count;
	addr = malloc(size);
	if (addr)
		ft_bzero(addr, size);
	return (addr);
}
