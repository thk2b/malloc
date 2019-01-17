#include <shared.h>

void	block__show_alloc(t_block *block, void *ctx)
{
	UNUSED(ctx);
	put_str(1, "Block\t");
	put_hex(1, block__data(block), 1);
	put_str(1, block->free ? "\tF\t" : "\tU\t");
	put_hex(1, block->size, 1);
	put_str(1, " bytes\n");
}
