#include <sys/mman.h>
#include <unistd.h>
#include <shared.h>
#include <assert.h>

static int	area__find_can_fit(t_area *a, void *ctx)
{
	size_t	size;

	size = *(size_t*)ctx;
	return (AREA__CAN_FIT(a, size + sizeof(t_block)));
}

static int	area__find_prev(t_area *a, void *ctx)
{
	return ((void*)a < ctx && (void*)a->next > ctx);
}

static void	*request_mem(void *addr, size_t size)
{
	size_t	pgsz;
	size_t	min_sz;
	t_area	*a;

	pgsz = getpagesize();
	min_sz = PGS_PER_MAP * pgsz;
	size = MAX(ALLIGN(size, pgsz), min_sz);
	a = (t_area*)mmap(addr, size, PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (a == MAP_FAILED)
		return (NULL);
	a->size = size;
	a->cur_size = sizeof(t_area);
	a->is_single_block = a->size > min_sz;
	return (a);
}

t_area			*area_list__insert(t_area_list *al, t_area *a)
{
	t_area	*prev;
	t_area	*next;

	if ((void*)(al->tail) < (void*)a)
	{
		next = NULL;
		prev = al->head;
		al->tail = a;
	}
	else if ((void*)a < (void*)(al->head))
	{
		next = al->head;
		prev = NULL;
		al->head = a;
	}
	else
	{
		prev = area_list__search(al, area__find_prev, (void*)a);
		assert(prev);
		assert(prev->prev);
		assert(prev->next);
		next = prev->next;
	}
	if (prev && AREA__IS_END(prev, a))
	{
		area__extend(prev, a->size);
		return (prev);
	}
	if (prev)
		prev->next = a;
	a->prev = prev;
	if (next)
		next->prev = a;
	a->next = next;
	return (a);
}

t_area		*area_list__request_mem(t_area_list* al, size_t size)
{
	t_area	*a;

	a = area_list__search(al, area__find_can_fit, &size);
	if (a)
		return (a);
	a = request_mem(al->tail, size);
	a = area_list__insert(al, a);
	#ifdef LOG
	area__log(a, "new area");
	#endif
	return (a);
}

t_area		*area_list__search(t_area_list *al, t_area_list__search_fn fn, void *ctx)
{
	t_area	*a;

	a = al->head;
	while (a)
	{
		if (fn(a, ctx))
			return (a);
		a = a->next;
	}
	return (NULL);
}

void		area_list__foreach(t_area_list *al, t_area_list__foreach_fn fn, void *ctx)
{
	t_area	*a;

	a = al->head;
	while (a)
	{
		fn(a, ctx);
		a = a->next;
	}
}

#ifdef LOG
void		area_list__log(t_area_list *al, char *msg)
{
	UNUSED(al);
	UNUSED(msg);
}
#endif
