#include <ft_malloc.h>
#include <string.h>

t_area	*new_area(size_t size)
{
	size_t	pg_size;
	size_t	alloc_size;
	t_area	*area;

	pg_size = getpagesize();
	alloc_size = pg_size * PAGES_PER_MAP;
	if (size < alloc_size)
		size = alloc_size;
	else
		size += sizeof(t_area);
	size = ALLIGN(size, pg_size);
	area = (t_area*)mmap(NULL,
		size,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,
		-1, 0);
	if (area == MAP_FAILED)
		return (NULL);
	area->size = size;
	area->cur_size = 0;
	area->next = NULL;
	return (area);
}

void	append_area(t_area *a, t_area *b)
{
	a->next = b;
}
