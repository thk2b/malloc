#include <ft_malloc.h>
#include <unistd.h>

extern void	*malloc(size_t size)
{
	extern t_page	*g_zones;
	t_page			*page;
	t_block			*block;

	page = get_zone(&g_zones, size);
	block = get_free_block(page, size);
	if (block->size > size && block->size - size > page->min_block_size)
		split_block(block);
	return (block->data);
}
