#include <shared.h>

int		free_list__find_first_fit_coalesce(t_area *a, t_free_block *fb, t_free_block **next, void *ctx)
{
	size_t			requested_size;
	t_free_block	*new_fb;
	t_free_block	*last_encountered_adjacent_fb;

	requested_size = *(size_t*)ctx;
	if (fb->block.size >= requested_size)
		return (0);
	last_encountered_adjacent_fb = NULL;
	new_fb = area__coalesce(a, fb, requested_size, &last_encountered_adjacent_fb);
	*next = last_encountered_adjacent_fb;
	if (new_fb == NULL)
		return (0);
	return (1);
}
