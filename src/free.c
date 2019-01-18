#include <malloc.h>
#include <shared.h>

extern t_free_list	g_free_lists[];
extern t_area_list	g_area_list;

extern void			free(void *ptr)
{
	t_area			*a;
	t_block			*b;
	t_free_block	*fb;
	t_free_list		*fl;

	a = area_list__search(&g_area_list, area__find_in_range, ptr);
	if (a)
		b = area__search(a, block__find_address, ptr);
/*		b = block__from_ptr(ptr);*/
	if (a == NULL || b == NULL)
	{
		error__ptr_was_not_allocated("free", ptr);
		return ;
	}
	fb = area__deallocate_block(a, b);
	fl = free_list__find(g_free_lists, b->size);
	free_list__insert(fl, a, fb);
}
