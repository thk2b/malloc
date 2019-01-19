#include <shared.h>
#include <assert.h>

int				area__can_fit(t_area *a, size_t size)
{
	assert(a->size > a->cur_size);
	return (a->size - a->cur_size > size);
}

void			area__extend(t_area *a, size_t extention_size)
{
	if (a->is_single_block)
		a->is_single_block = 0;
	a->size += extention_size;
	#ifdef LOG
	area__log(a, "extended");
	#endif
}

t_block			*area__allocate_new_block(t_area *a, size_t size)
{
	t_block	*b;

	assert(AREA__CAN_FIT(a, size + sizeof(t_block)));
	b = block__allocate((void*)((char*)a + a->cur_size), size);
	a->cur_size += size + sizeof(t_block);
	#ifdef LOG
	block__log(b, "new");
	#endif
	return (b);
}

t_free_block	*area__deallocate_block(t_area *a, t_block *b)
{
	t_free_block	*fb;
	t_block			*next;

	next = BLOCK__NEXT(b);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__deallocate_prev(next);
	fb = free_block__deallocate(b);
	return (fb);
}

t_block			*area__allocate_free_block(t_area *a, t_free_block *fb)
{
	t_block	*b;
	t_block	*next;

	next = BLOCK__NEXT(&fb->block);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__allocate_prev(next);
	b = free_block__allocate(fb);
	return (b);
}

void			area__foreach(t_area *a, t_area__foreach_fn fn, void *ctx)
{
	t_block	*b;
	void	*end;
	size_t	index;

	index = 0;
	end = AREA__CUR_END(a);
	b = AREA__HEAD(a);
	while ((void*)b < end)
	{
		fn(b, index++, ctx);
		b = BLOCK__NEXT(b);
	}
}

t_block			*area__search(t_area *a, t_area__search_fn fn, void *ctx)
{
	t_block	*b;
	void	*end;

	end = AREA__CUR_END(a);
	b = AREA__HEAD(a);
	while ((void*)b < end)
	{
		if (fn(b, ctx))
			return (b);
		b = BLOCK__NEXT(b);
	}
	return (NULL);
}

int				area__find_in_range(t_area *a, void *ctx)
{
	return (AREA__IS_IN_BOUNDS(a, ctx));
}

int				area__find_has_free_block(t_area *a, void *ctx)
{
	return (AREA__HAS_FREE_BLOCK(a, *(size_t*)ctx));
}

void			area__hexdump(t_area *a, size_t index, void *ctx)
{
	UNUSED(index);
	UNUSED(ctx);
	hexdump((void*)a, sizeof(t_area), AREA__HEADER_COLOR);
	area__foreach(a, block__hexdump, NULL);
	hexdump((void*)AREA__CUR_END(a), AREA__AVAILABLE_SIZE(a), AREA__REMAINING_COLOR);
	put_str(1, a->next ? "\n    ⋮\n" : "\n");
}

void			area__show_alloc(t_area *area, size_t index, void *ctx)
{
	*(size_t*)ctx += area->size;
	put_str(1, "Area ");
	put_dec(1, index);
	put_str(1, "\n");
	area__foreach(area, block__show_alloc, NULL);
	put_dec(1, area->cur_size);
	put_str(1, "/");
	put_dec(1, area->size);
	put_str(1, " bytes\n");
}

#ifdef LOG
void			area__log(t_area *a, char *msg)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	log__line_count(fd);
	put_str(fd, msg);
	put_str(fd, "\t");
	put_str(fd, "area\t\t");
	put_hex(fd, (size_t)a, 1);
	put_str(fd, "\t");
	put_dec(fd, a->size);
	put_str(fd, "\n");
}
#endif
