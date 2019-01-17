#include <malloc.h>

static void	print_block(t_block *block)
{
	put_str(1, "\tblock ");
	put_str(1, block->free ? "f\t" : "u\t");
	put_dec(1, block->size);
	put_str(1, "\t");
	put_hex(1, (size_t)DATA(block), 1);
	put_str(1, "\n");
}

static void	print_area(t_area *area, size_t i)
{
	t_block	*block;
	void	*area_cur_end;
	void	*area_end;

	area_cur_end = (void*)((char*)area + area->cur_size);
	area_end = (void*)((char*)area + area->size);
	block = (t_block*)((char*)area + sizeof(t_area));
	put_str(1, "area\t");
	put_dec(1, i);
	put_str(1, "\t");
	put_hex(1, (size_t)area, 1);
	put_str(1, "\t");
	put_dec(1, area->cur_size);
	put_str(1, " / ");
	put_dec(1, area->size);
	put_str(1, "\n");
	while ((void*)block < area_cur_end)
	{
		print_block(block);
		block = (t_block*)((char*)block + sizeof(t_block) + block->size);
	}
}

/*
**	Prints information about all blocks present in the heap
*/

void	show_alloc_mem(void)
{
	extern t_area	*g_area_head;
	t_area			*area;
	size_t	i;
	size_t	total_cur;
	size_t	total;

	i = 0;
	total = 0;
	total_cur = 0;
	area = g_area_head;
	while (area)
	{
		print_area(area, i++);
		total += area->size;
		total_cur += area->cur_size;
		area = area->next;
	}
	put_str(1, "summary\n");
	put_dec(1, total_cur);
	put_str(1, "\tbytes allocated\n");
	put_dec(1, total);
	put_str(1, "\tbytes footprint\n");
}
