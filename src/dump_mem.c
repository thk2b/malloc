#include <shared.h>

extern t_area_list	*g_area_list;

void	dump_mem(void)
{
	int	fd;

	fd = 1;
	area_list__foreach(g_area_list, area__hexdump, &fd);
}
