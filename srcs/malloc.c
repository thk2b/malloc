#include <ft_malloc.h>
#include <unistd.h>

extern void	*malloc(size_t size)
{
	t_page			*page;
	t_block			*block;

	size = ALLIGN(size, 8);
	page = get_zone(size);
	if ((block = get_free_block(page, size)) == NULL)
		return (NULL);
	if (block->size > size && block->size - size > page->min_block_size)
		split_block(block);
	return (block->data);
}
