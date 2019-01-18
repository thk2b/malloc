#include <shared.h>

extern t_area_list	g_area_list;

void	show_alloc_mem(void)
{
	area_list__show_alloc_mem(&g_area_list);
}
