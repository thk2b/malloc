#include <shared.h>

extern t_free_list	g_free_lists[];

size_t				area__count_free_space_after(t_area *a, t_block *b, size_t until, t_free_block **last_encountered_fb)
{
	size_t			count;
	t_block			*cur;
	void			*end;
	t_free_block	*local_lefb;
	t_free_list		*fl;

	if (b->free)
		fl = free_list__find(g_free_lists, b->size);
	end = AREA__CUR_END(a);
	count = 0;
	cur = BLOCK__NEXT(b);
	while ((void*)cur < end && count < until && cur->free)
	{
		if (fl == free_list__find(g_free_lists, cur->size))
			local_lefb = (t_free_block*)cur;
		count += cur->size + sizeof(t_block);
		cur = BLOCK__NEXT(b);
	}
	if ((void*)cur == end)
		return (AREA__CAN_FIT(a, until - count) ? until : count);
	if (last_encountered_fb)
		*last_encountered_fb = local_lefb;
	return (count);
}

size_t				area__count_free_space_before(t_area *a, t_block *b, size_t until)
{
	size_t			count;
	t_block			*cur;
	void			*end;

	end = AREA__HEAD(a);
	count = 0;
	if (b->prev_free == 0)
		return (0);
	cur = BLOCK__PREV(b);
	while ((void*)cur > end && count < until && cur->free)
	{
		count += cur->size + sizeof(t_block);
		if (cur->prev_free == 0)
			break ;
		cur = BLOCK__PREV(b);
	}
	return (count);
}
