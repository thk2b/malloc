#include <ft_malloc.h>
#include <string.h>

void	init_area(t_area *area, size_t size)
{
	area->size = size;
	area->cur_size = 0;
	area->next = NULL;
	area->free_head = NULL;
}

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
	area = (t_area*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (area == MAP_FAILED)
	{
		write(2, "ERROR: mmap failed\n", 20);
		return (NULL);
	}
	init_area(area, size);
	return (area);
}

void	append_area(t_area *a, t_area *b)
{
	if (a)
		a->next = b;
}

void	del_area(t_area *area)
{
	(void)area;
	return ;
}
