#include <malloc.h>
#include <shared.h>
#include <area_list.h>
#include <block.h>
#include <free_list.h>
#include <free_block.h>

extern void	free(void *ptr)
{
	t_area			*a;
	t_block			*b;
	t_free_block	*fb;
	t_free_list		*fl;

	a = area_list__search(g_area_list, address_in_range, ptr);
	if (a)
		b = block__from_ptr(ptr);
	if (a == NULL || b == NULL)
		return (error__ptr_was_not_allocated(ptr));
	fb = area__deallocate_block(a, b);
	fl = free_list__find(g_free_lists, b->size);
	free_list__insert(fl, a, fb);
}
