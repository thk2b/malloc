#include <assert.h>
#include <shared.h>

static inline void	write_boundary_tag(t_free_block *fb)
{
	size_t	*addr;

	addr = (size_t*)BLOCK__NEXT(&fb->block) - 1;
	*addr = fb->block.size;
}

t_free_block		*free_block__deallocate(t_block *b)
{
	t_free_block	*fb;

	assert(b->size + sizeof(t_block) >= sizeof(t_free_block) + sizeof(size_t));
	fb = (t_free_block*)b;
	fb->block.free = 1;
	write_boundary_tag(fb);
	return (fb);
}

t_block				*free_block__allocate(t_free_block *fb)
{
	t_block			*b;

	b = &fb->block;
	fb->next = NULL;//FIXME: remove
	fb->prev = NULL;
	fb->block.free = 1;
	return (b);
}

void				free_block__hexdump(t_free_block *fb, size_t index, void *ctx)
{
	UNUSED(index);
	UNUSED(ctx);
	hexdump((void*)fb, sizeof(t_block), FREE_BLOCK__BLOCK_COLOR);
	hexdump((void*)BLOCK__DATA(&fb->block), sizeof(t_free_block) - sizeof(t_block), FREE_BLOCK__POINTERS_COLOR);
	hexdump((void*)((char*)fb + sizeof(t_free_block)), fb->block.size - FREE_BLOCK__MIN_SIZE, FREE_BLOCK__DATA_COLOR);
	hexdump((void*)((char*)BLOCK__NEXT(&fb->block) - sizeof(size_t)), sizeof(size_t), FREE_BLOCK__FOOTER_COLOR);
}
