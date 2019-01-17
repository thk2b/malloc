#include <malloc.h>
#include <shared.h>
#include <area_list.h>
#include <block.h>
#include <free_list.h>
#include <free_block.h>

extern void	*malloc(size_t size)
{
	t_free_list		*fl;
	t_area			*a;
	t_free_block	*fb;
	t_block			*b;

	size = ALLIGN(size, 8);
	fl = free_list__find(g_free_lists, size);
	fb = free_list__search(fl, &area, first_fit, (void*)&size);
	if (fb)
		b = area__allocate_free_block(area, fb);
	else if ((area = area_list__request_mem(g_area_list, size)))
		b = area__allocate_new_block(area, size);
	else
		return (error__no_mem());
	return (block__data(b));
}
