#include <ft_malloc.h>

void	show_alloc_mem_zone(size_t i, t_page *page)
{
	t_page	*cur;
	t_block	*block;

	cur = page;
	printf("=== zone %zu ===\n", i);
	while (cur)
	{
		block = cur->head;
		while (block)
		{
			printf("\t%p: %zu bytes\n", block->data, block->size);
			block = block->next;
		}
	}
}

void	show_alloc_mem(void)
{
	extern t_page	*g_zones;
	size_t			i;

	i = 0;
	while (i < NZONES)
	{
		show_alloc_mem_zone(i, g_zones + i);
		i++;
	}
}
