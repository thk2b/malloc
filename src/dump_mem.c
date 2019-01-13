#include <malloc.h>

static void	dump_area_header(t_area *area)
{

}

static void	dump_block_header(t_block *block)
{

}

static void	dump_block_body(t_block *block)
{

}

static void	dump_area_body(t_area *area)
{

}

/*
**	Prints a hexdump of the heap
*/

void	dump_mem(void)
{
	extern t_area	*g_area_head;
	t_area			*area;

	area = g_area_head;
	while (area)
	{
		dump_area_header(area);
		dump_area_body(area);
		area = area->next;
	}
}
