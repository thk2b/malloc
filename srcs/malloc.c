#include <ft_malloc.h>

void	*malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	size = ALLIGN(size, 8);
	zone = get_zone(size);
	if ((block = find_block(zone->head)) == NULL)
		return (NULL);
	if (0 && B_SIZE(block) > size && B_SIZE(block) - (size + sizeof(t_block)) > zone->min_block_size)
		split_block(block, size);
	return (B_DATA(block));
}
