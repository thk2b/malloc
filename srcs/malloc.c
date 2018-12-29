#include <ft_malloc.h>
#include <stdio.h>
#include <signal.h>

extern void	*malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	if (size == 0)
		size = 1;
	size = ALLIGN(size, 8);
# ifdef LIBFT_MALLOC_LOG
	dprintf(2, "malloc(%zu) -> ", size);
# endif
	zone = get_zone(size);
	if (zone->head == NULL && (zone->head = new_area(size)) == NULL)
	{
		return (NULL);
	}
	if ((block = find_free_block(zone->head, size)) == NULL)
	{
		return (NULL);
	}
	if (0 && B_SIZE(block) > size && B_SIZE(block) - (size + sizeof(t_block)) > zone->min_block_size)
		split_block(block, size);
# ifdef LIBFT_MALLOC_LOG
	dprintf(2, "%p\n", B_DATA(block));
# endif
	return (B_DATA(block));
}
