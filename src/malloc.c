#include <malloc.h>
#include <shared.h>

extern t_free_list	g_free_lists[];
extern t_area_list	*g_area_list;

extern void	*malloc(size_t size)
{
	t_free_list		*fl;
	t_area			*a;
	t_free_block	*fb;
	t_block			*b;

	size = ALLIGN(size, 8);
	fl = free_list__find(g_free_lists, size);
	fb = free_list__search(fl, &a, free_list__first_fit, (void*)&size);
	if (fb)
		b = area__allocate_free_block(a, fb);
	else if ((a = area_list__request_mem(g_area_list, size)))
		b = area__allocate_new_block(a, size);
	else
		return (error__no_mem());
	return (block__data(b));
}
