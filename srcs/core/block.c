#include <ft_malloc.h>

static inline	t_block	*find_free_block_in_area(t_area *area, size_t size)
{
	
}

t_block	*find_free_block(t_area *area, size_t size)
{
	t_area	*prev_area;
	t_block	*prev_block;
	t_block	*block;

	area = area;
	(void)size;
	while (area)
	{
		block = A_HEAD(area);
		while (block)
		{
			if (B_IS_FREE(block) && B_SIZE(block) >= size)
				return (block);
			prev_block = block;
			block = B_NEXT(block);
		}
		prev_area = area;
		area = area->next;
	}
	if (area == NULL && (area = new_area(size)) == NULL)
			return (NULL);
	append_area(prev_area, area);
	if (A_CAN_FIT(area, size + sizeof(t_block)))
	{
		block = prev_block ? B_NEXT(prev_block) : A_HEAD(area);
		new_block(block, size);
		append_block(prev_block , block);
	}
	return (NULL);
}
