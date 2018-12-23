#include <ft_malloc.h>

void	init_block(t_block *block, t_block *prev, size_t size)
{
	block->prev = prev;
	block->next = NULL;
	block->data = (void*)((char*)block + sizeof(t_block));
	block->size = size;
	block->next = NULL;
	if (prev)
		prev->next = block;
}

t_block			*append_new_block(t_page *page, t_block *prev, size_t size)
{
	t_block		*new_block;
	size_t		new_page_size;

	new_page_size = page->cur_size + sizeof(t_block) + size;
	if (page->cur_size + new_page_size >= page->size)
		return (NULL);
	new_block = prev ?
		(t_block*)((char*)prev + sizeof(t_block) + prev->size) : (t_block*)((char*)page + sizeof(t_page));
	init_block(new_block, prev, size);
	if (page->head == NULL)
		page->head = new_block;
	page->cur_size = new_page_size;
	return (new_block);
}

void			split_block(t_block *block, size_t size)
{
	t_block		*new_block;
	t_block		*next;

	new_block = (t_block*)((char*)block + sizeof(t_block) + size);
	next = block->next;
	init_block(new_block, block, block->size - size);
	block->size = size;
	new_block->next = next;
}
