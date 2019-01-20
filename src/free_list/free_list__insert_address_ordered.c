#include <shared.h>
#include <assert.h>

static int		find_prev_free_block(t_area *area, t_free_block *fb, void *ctx)
{
	UNUSED(area);
	return ((void*)fb < ctx && (fb->next == NULL || ctx < (void*)fb->next));
}

void			free_list__insert_address_ordered(t_free_list *fl, t_area *a, t_free_block *fb)
{
	t_area			*prev_block_area;
	t_free_block	*prev;
	t_free_block	*next;

	UNUSED(a);
	prev = free_list__search(fl, &prev_block_area, find_prev_free_block, (void*)fb);
	next = prev ? prev->next : fl->head;
	assert((void*)prev < (void*)fb && ((void*)next == NULL || (void*)fb < (void*)next));
	if (prev == NULL)
		fl->head = fb;
	if (prev)
		prev->next = fb;
	fb->prev = prev;
	if (next)
		next->prev = fb;
	fb->next = next;
}
