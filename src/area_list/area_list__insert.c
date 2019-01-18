#include <shared.h>

static int	area__find_prev(t_area *a, void *ctx)
{
	return ((void*)a < ctx && (a->next == NULL || (void*)a->next > ctx));
}

static t_area	*area_list__init(t_area_list *al, t_area *a)
{
	#ifdef LOG
	area__log(a, "new");
	#endif
	al->head = a;
	al->tail = a;
	return (a);
}

t_area			*area_list__insert(t_area_list *al, t_area *a)
{
	t_area	*prev;
	t_area	*next;

	if (al->head == NULL)
		return (area_list__init(al, a));
	prev = area_list__search(al, area__find_prev, a);
	next = prev ? prev->next : al->head;
	if (prev && AREA__IS_END(prev, a))
	{
		area__extend(prev, a->size);
		return (prev);
	}
	if (prev == NULL)
		al->head = a;
	else if (prev->next == NULL)
		al->tail = a;
	if (prev)
		prev->next = a;
	a->prev = prev;
	if (next)
		next->prev = a;
	a->next = next;
	#ifdef LOG
	area__log(a, "new");
	#endif
	return (a);
}
