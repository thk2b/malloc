#include <shared.h>

t_free_block	*free_list__find_first_fit_coalesce(t_area *a, t_free_block *fb, char *flag, void *ctx)
{
	size_t			requested_size;
	t_free_block	*new_fb;
	t_free_block	*last_encountered_adjacent_fb;

	requested_size = *(size_t*)ctx;
	if (fb->block.size >= requested_size)
		return (fb);
	new_fb = area__coalesce(a, fb, requested_size, &last_encountered_adjacent_fb);
	if (new_fb == NULL)
		return (last_encountered_adjacent_fb);
	*flag = 1;
	return (new_fb);
}
