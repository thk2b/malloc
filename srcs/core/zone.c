#include <ft_malloc.h>

t_zone	g_zones[] = {
	{0, NULL},
	{ZONE_S_SZ + 1, NULL},
	{ZONE_M_SZ + 1, NULL},
};

t_zone	*get_zone(size_t size)
{
	size_t	i;

	i = 1;
	while (i < N_ZONES && size >= g_zones[i].min_block_size)
		i++;
	return (g_zones + (i - 1));
}
