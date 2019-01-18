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

static void	*request_mem(void *addr, size_t size)
{
	size_t	pgsz;
	size_t	min_sz;
	t_area	*a;

	pgsz = getpagesize();
	min_sz = PGS_PER_MAP * pgsz;
	size = MAX(ALLIGN(size, pgsz), min_sz);
	a = (t_area*)mmap((char*)addr, size, PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (a == MAP_FAILED)
		return (NULL);
	a->size = size;
	a->cur_size = sizeof(t_area);
	a->is_single_block = a->size > min_sz;
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
	size_t	index;

	index = 0;
	a = al->head;
	while (a)
	{
		fn(a, index++, ctx);
		a = a->next;
	}
}

void		area_list__show_alloc_mem(t_area_list *al)
{
	size_t	total;

	total = 0;
	area_list__foreach(al, area__show_alloc, (void*)&total);
	put_str(1, "Total ");
	put_dec(1, total);
	put_str(1, " bytes\n");
}

#ifdef LOG
void		area_list__log(t_area_list *al, char *msg)
{
	UNUSED(al);
	UNUSED(msg);
}
#endif
