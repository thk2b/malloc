#include <shared.h>

t_block	*block__allocate(void *addr, size_t size)
{
	t_block	*b;

	b = (t_block*)addr;
	b->prev_free = 0;
	b->free = 0;
	b->size = size;
	b->chksum = 0;//TODO: Implement
	return (b);
}

void	block__show_alloc(t_block *block, void *ctx)
{
	UNUSED(ctx);
	put_str(1, "\tBlock\t");
	put_hex(1, (size_t)BLOCK__DATA(block), 1);
	put_str(1, block->free ? "\tF\t" : "\tU\t");
	put_num(1, block->size);
	put_str(1, " bytes\n");
}

void	block__hexdump(t_block *b, void *ctx)
{
	UNUSED(ctx);
	hexdump((void*)b, sizeof(t_block), BLOCK__HEADER_COLOR);
	hexdump(BLOCK__DATA(b), b->size, BLOCK__DATA_COLOR);
}

#ifdef LOG 
void	block__log(t_block *b, char *msg)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	log__line_count(fd);
	put_str(fd, "block\t");
	put_hex(fd, (size_t)b, 1);
	put_str(fd, "\t");
	put_dec(fd, b->size);
	put_str(fd, "\t");
	put_str(fd, msg);
	put_str(fd, "\n");
}
#endif
