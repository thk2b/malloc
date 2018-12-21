#include <ft_malloc.h>
#include <libft.h>

void	show_alloc_mem_zone(size_t i, t_page *page)
{
	t_page	*cur;
	t_block	*block;
	size_t	total;
	size_t	n_blocks;

	total = 0;
	n_blocks = 0;
	cur = page;
	printf("=== zone %zu ===\n", i);
	while (cur)
	{
		block = cur->head;
		while (block)
		{
			n_blocks++;
			total += block->size;
			printf("\t%p: %zu bytes\n", block->data, block->size);
			block = block->next;
		}
		cur = cur->next;
	}
	printf("\ttotal: %zu bytes in %zu blocks\n", total, n_blocks);
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
