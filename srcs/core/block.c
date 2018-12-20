#include <ft_malloc.h>

void	init_block(t_block *block, t_block *prev, size_t size)
{
	block->prev = block;
	block->next = prev;
	block->data = NULL;
	block->size = size;
}

t_block	*append_new_block(t_page *page, t_block *prev, size_t size)
{
	size_t	new_page_size;

	new_page_size = page->cur_size + size;

	if (prev == NULL || new_page_size >= page->size)
		return (NULL);
	prev->next = prev->data + prev->size;
	init_block(prev->next, prev, size);
	page->cur_size = new_page_size;
	return (prev->next);
}
