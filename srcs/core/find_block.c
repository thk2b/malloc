#include <ft_malloc.h>

t_block		*find_block(void *ptr)
{
	extern t_page	g_zones[];
	t_page			*page;
	t_block			*block;
	size_t			zone_i;

	zone_i = 0;
	while (zone_i < NZONES)
	{
		page = g_zones + zone_i;
		while (page)
		{
			block = page->head;
			while (block)
			{
				if (block->data == ptr)
					return (block);
				block = block->next;
			}
			page = page->next;
		}
		zone_i++;
	}
	dprintf(2, ">%p\n", ptr);
	return (NULL);
}
