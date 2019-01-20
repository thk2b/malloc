#include <shared.h>
#include <assert.h>

extern t_free_list	g_free_lists[];

/*
**	Resize b to target size and create a new free block with the remainder
**	target size must be 8 byte alligned and smaller than the block
*/
void	area__split_free_block(t_area *a, t_free_block *fb, size_t target_size)
{
	size_t			new_block_size;
	t_free_block	*new_block;
	t_free_list		*fl;

	assert(fb->block.size >= target_size);
	new_block_size = fb->block.size - target_size - sizeof(t_block);
	if (new_block_size < FREE_BLOCK__MIN_SIZE)
		return ;
	free_list__remove(free_list__find(g_free_lists, fb->block.size), a, fb);
	fb->block.size = target_size;
	free_list__insert(free_list__find(g_free_lists, fb->block.size), a, fb);
	new_block = (t_free_block*)BLOCK__NEXT(&fb->block);
	new_block->block.size = new_block_size;
	new_block->block.free = 0;//to pass assertion
	area__deallocate_block(a, &new_block->block);
	fl = free_list__find(g_free_lists, new_block_size);
	free_list__insert(fl, a, new_block);
}
