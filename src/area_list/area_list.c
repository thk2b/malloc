#include <sys/mman.h>
#include <unistd.h>
#include <shared.h>
#include <assert.h>

static int	area__find_can_fit(t_area *a, void *ctx)
{
	size_t	size;

	size = *(size_t*)ctx;
	if (a->is_single_block)
		return (0);
	return (AREA__CAN_FIT(a, size));
}

static void	*request_mem(void *addr, size_t size)
{
	size_t	pgsz;
	size_t	min_sz;
	t_area	*a;

	pgsz = getpagesize();
	min_sz = PGS_PER_MAP * pgsz;
	size = MAX(ALLIGN(size, pgsz), min_sz);
	a = (t_area*)mmap((char*)addr, size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (a == MAP_FAILED)
		return (error__no_mem("mmap"));
	a->size = size;
	a->cur_size = sizeof(t_area);
	a->is_single_block = a->size > min_sz;
	return (a);
}

t_area		*area_list__request_mem(t_area_list* al, size_t size)
{
	t_area	*a;
	size_t	total_size;

	total_size = size + sizeof(t_block);
	a = area_list__search(al, area__find_can_fit, &total_size);
	if (a)
		return (a);
	a = request_mem(al->tail, total_size);
	if (a == NULL)
		return (NULL);
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

t_area			*area_list__search_around(t_area *a, t_area_list__search_fn fn, void *ctx)
{
	char	direction;
	t_area	*left;
	t_area	*right;
	t_area	*cur;

	cur = a;
	left = a->prev;
	right = a->next;
	direction = 0;
	while (left || right)
	{
		if (right == NULL)
		{
			cur = left;
			left = left->prev;
		}
		else if (left == NULL)
		{
			cur = right;
			right = right->next;
		}
		else if (direction == 0)
		{
			cur = left;
			left = left->prev;
		}
		else if (direction == 1)
		{
			cur = right;
			right = right->next;
		}
		if (cur == NULL)
			break ;
		assert(cur != a);
		direction = !direction;
		if (fn(cur, ctx))
			return (cur);
	}
	return (NULL);
}

t_area		*area_list__search_from(t_area *start, t_area_list__search_fn fn, void *ctx)
{
	t_area	*a;

	a = start;
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

void		area_list__remove(t_area_list *al, t_area *a)
{
	if (al->head == a)
		al->head = a->next;
	if (a->prev)
		a->prev->next = a->next;
	if (a->next)
		a->next->prev = a->prev;
	a->next = NULL;
	a->prev = NULL;
	#ifdef LOG
	area__log(a, "remove");
	#endif
	munmap((void*)a, a->size);
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
