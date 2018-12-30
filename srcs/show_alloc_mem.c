#include <ft_malloc.h>
#include <stdio.h>

void		show_block(t_block *block)
{
	printf("\t%p\t%zu (%s)\n", block, block->size, block->used ? "A":"F");
	// ft_putstr("\t");
	// ft_putaddr((void *)block);
	// ft_putstr("\t");
	// ft_putnbr(block->size);
	// ft_putstr("\n");
}

void		show_area(t_area *area, size_t *total, size_t *nblocks)
{
	t_block	*block;
	void	*end;

	end = A_CUR_END(area);
	block = A_HEAD(area);
	while (block && (void*)block < end)
	{
		*total += block->size;
		(*nblocks)++;
		show_block(block);
		block = B_NEXT(block);
	}
}

void		show_zone(t_zone *zone, size_t i)
{
	t_area	*area;
	size_t	nblocks;
	size_t	total;

	printf("== zone  %zu ==\n", i);
	// ft_putstr("== zone ");
	// ft_putnbr(i);
	// ft_putstr(" ==\n");
	total = 0;
	nblocks = 0;
	if ((area = zone->head) == NULL)
		return ;
	while (area)
	{
		show_area(area, &total, &nblocks);
		area = area->next;
	}
	printf("%zu bytes in %zu blocks\n", total, nblocks);
}

extern void	show_alloc_mem(void)
{
	extern t_zone	g_zones[];
	size_t			i;

	i = 0;
	while (i < N_ZONES)
	{
		show_zone(g_zones + i, i);
		i++;
	}
}
