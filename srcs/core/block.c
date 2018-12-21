#include <ft_malloc.h>

void	init_block(t_block *block, t_block *prev, size_t size)
{
	block->prev = block;
	block->next = prev;
	block->data = block + sizeof(t_block);
	block->size = size;
	block->next = NULL;
}

t_block			*append_new_block(t_page *page, t_block *prev, size_t size)
{
	t_block		*new_block;
	size_t		new_page_size;

	new_page_size = sizeof(t_page) + size;
	if (prev == NULL || page->cur_size + new_page_size >= page->size)
		return (NULL);
	new_block = prev + sizeof(t_block) + prev->size;
	init_block(new_block, prev, size);
	if (page->head == NULL)
		page->head = new_block;
	prev->next = new_block;
	page->cur_size = new_page_size;
	return (new_block);
}

int		split_block(t_block *block)
{
	(void)block;
	return (1);
}
