#include <ft_malloc.h>

static inline void	merge_blocks(t_block *a, t_block *b)
{
	a->size += b->size + sizeof(t_block);
	a->next = b->next;
	if (b->next)
		b->next->prev = a;
}

static inline void	coalesce(t_block *block)
{
	if (block->prev && IS_FREE(block->prev))
		merge_blocks(block->prev, block);
	if (block->next && IS_FREE(block->next))
		merge_blocks(block, block->next);
}

extern void			free(void *ptr)
{
	t_block	*block;

	if (ptr == NULL)
		return ;
	if ((block = find_block(ptr)) == NULL)
	{
		// write(2, "pointer was not allocated\n", 27);
		return ;
	}
	block->data = NULL;
	coalesce(block);
}
