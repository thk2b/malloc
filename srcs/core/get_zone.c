#include <ft_malloc.h>

t_page	*get_zone(t_page **zones, size_t size)
{
	size_t	i;

	i = 1;
	while (zones[i])
		if (size < zones[i]->min_block_size)
			return (zones[i - 1]);
		else
			i++;
	return (zones[i - 1]);
}
