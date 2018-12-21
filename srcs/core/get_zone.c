#include <ft_malloc.h>

t_page	*get_zone(size_t size)
{
	extern t_page	g_zones[];
	size_t	i;

	i = 1;
	while (i < NZONES && size > g_zones[i].min_block_size)
		i++;
	return (g_zones + (i - 1));
}
