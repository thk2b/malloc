#include <ft_malloc.h>

void		show_block(t_block *block)
{
	ft_putstr("\t");
	ft_putaddr((void *)block);
	ft_putstr("\n");
}

void		show_area(t_area *area)
{
	t_block	*block;

	ft_putstr("\t ==\n");
	block = A_HEAD(area);
	while (block)
	{
		show_block(block);
		block = B_NEXT(block);
	}
}

void		show_zone(t_zone *zone, size_t i)
{
	t_area	*area;

	ft_putstr("== zone ");
	ft_putnbr(i);
	ft_putstr(" ==\n");
	area = zone->head;
	while (area)
	{
		show_area(area);
		area = A_NEXT(area);
	}
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
