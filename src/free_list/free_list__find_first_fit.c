#include <shared.h>
#include <assert.h>

int		free_list__find_first_fit(t_area *a, t_free_block *fb, void *ctx)
{
	size_t	size;

	UNUSED(a);
	assert(fb->block.free);
	size = *(size_t*)ctx;
	return (fb->block.size >= size);
}
