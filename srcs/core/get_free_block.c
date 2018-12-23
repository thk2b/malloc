#include <ft_malloc.h>

static inline t_block
				*get_free_block_in_page(t_page *page, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = page->head;
	prev = NULL;
	while (block)
	{
		if (IS_FREE(block) && block->size >= size)
		{
			block->data = (void*)((char*)block + sizeof(t_block));
			return (block);
		}
		prev = block;
		block = block->next;
	}
	return (append_new_block(page, prev, size));
}

t_block			*get_free_block(t_page *zone, size_t size)
{
	t_page	*page;
	t_page	*prev;
	t_block	*block;

	page = zone;
	block = NULL;
	while (page)
	{
		if ((block = get_free_block_in_page(page, size)))
			return (block);
		prev = page;
		page = page->next;
	}
	if ((page = append_page(prev, size)) == NULL)
		return (NULL);
	return (get_free_block_in_page(page, size));
}
