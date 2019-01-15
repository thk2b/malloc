#include <malloc.h>
#include <stdint.h>

static void	hexdump(void *ptr, size_t size, char *color)
{
	static size_t	count = 0;
	size_t			i;
	unsigned char	n;
	unsigned char	*d;

	if (ptr == NULL)
	{
		count = 0;
		return ;
	}
	i = 0;
	d = (unsigned char*)ptr;
	while (i < size)
	{
		if (count == 0)
		{
			put_str(1, ADDRESS);
			put_hex(1, (size_t)(d + i), 0);
			put_str(1, " ");
			put_str(1, RESET);
		}
		put_str(1, color);
		while (i < size && count++ < HEXDUMP_WIDTH)
		{
			n = d[i];
			i += 1;
			put_hex(1, (size_t)n, 0);
			if (n < 16)
				put_str(1, "0");
			put_str(1, " ");
		}
		if (i >= size)
			break ;
		count = 0;
		put_str(1, RESET "\n");
	}
	put_str(1, RESET);
}

static void	dump_area_header(t_area *area)
{
	hexdump(area, sizeof(t_area), AREA_HEADER);
}

static void	dump_block(t_block *block)
{
	hexdump(block, sizeof(t_block), BLOCK_HEADER);
	if (block->free)
	{
		hexdump(DATA(block), FREE_LIST_NODE_SIZE, FREE_LIST_NODE);
		hexdump((char*)block + sizeof(t_fblock), block->size - MIN_BLOCK_SIZE, FREE_BLOCK_REMAINDER);
		hexdump((char*)BLOCK_NEXT(block) - sizeof(size_t), sizeof(size_t), FREE_BLOCK_FOOTER);
	}
	else
		hexdump(DATA(block), block->size, BLOCK_DATA);
}

static void	dump_area_body(t_area *area)
{
	void	*area_cur_end;
	t_block	*block;

	area_cur_end = AREA_CUR_END(area);
	block = AREA_HEAD(area);
	while ((void*)block < area_cur_end)
	{
		dump_block(block);
		block = BLOCK_NEXT(block);
	}
	hexdump(area_cur_end, area->size - area->cur_size, AREA_UNUSED);
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
		put_str(1, RESET);
		hexdump(NULL, 0, NULL);
		put_str(1, area->next ? "\n    ⋮\n" : "\n");
		area = area->next;
	}
}
