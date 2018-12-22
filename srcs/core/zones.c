#include <ft_malloc.h>

t_page	g_zones[] = {
	{NULL, 0, 0, 0, NULL},
	{NULL, 0, 0, ZONE_S_SZ + 1, NULL},
	{NULL, 0, 0, ZONE_M_SZ + 1, NULL},
};

t_page	*get_zone(size_t size)
{
	extern t_page	g_zones[];
	size_t	i;

	i = 1;
	while (i < NZONES && size > g_zones[i].min_block_size)
		i++;
	return (g_zones + (i - 1));
}
