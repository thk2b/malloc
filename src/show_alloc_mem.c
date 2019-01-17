#include <shared.h>

extern t_area_list	*g_area_list;

void	show_alloc_mem(void)
{
	area_list__foreach(g_area_list, area__show_alloc, NULL);
}
