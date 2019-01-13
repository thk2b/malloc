#include <malloc.h>

#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

// static inline void	merge_areas(t_area *prev, t_area *next)
// {
	
// 	bzero(next, sizeof(t_area));
// }

static inline t_area	*init_new_area(t_area *area, size_t size)
{
	area->size = size;
	area->cur_size = sizeof(t_area);
	area->next = NULL;
	#ifdef MALLOC_LOG
	malloc_log_new_area(area);
	#endif
	return (area);
}

/*
**	link new area to existing ones
**		if areas area adjacent, merge them
*/
static inline t_area	*link_new_area(t_area *area, size_t size)
{
	extern t_area	*g_area_head;
	extern t_area	*g_area_tail;
	void			*prev_area_end;

	if (g_area_tail && (prev_area_end = AREA_END(g_area_tail)) == area)
	{
		g_area_tail->size += size;

		#ifdef MALLOC_LOG
		malloc_log_extended_area(g_area_tail);
		#endif
		return (g_area_tail);
	}
	if (g_area_tail)
		g_area_tail->next = area;
	else
		g_area_head = area;
	g_area_tail = area;
	return (init_new_area(area, size));
}

/*
**	create a new area
*/
t_area					*new_area(size_t size)
{
	extern t_area	*g_area_tail;
	size_t			pgsz;
	t_area			*area;

	pgsz = getpagesize();
	size = MAX(ALLIGN(size, pgsz), MIN_AREA_SIZE(pgsz));
	area = (t_area*)mmap((void*)g_area_tail, size,
		PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE,
		0, 0);
	if (area == MAP_FAILED)
		return (NULL);
	return (link_new_area(area, size));
}

/*
**	find an area with size available (O(n))
**		return NULL if not available
*/
t_area			*find_area_with_available_size(size_t size)
{
	extern t_area	*g_area_head;
	t_area			*area;

	if (g_area_head == NULL)
		return (NULL);
	area = g_area_head;
	while (area)
	{
		if (AREA_AVAILABLE_SIZE(area) >= size)
			return (area);
		area = area->next;
	}
	return (NULL);
}
