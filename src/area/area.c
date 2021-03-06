#include <shared.h>
#include <assert.h>
#include <string.h>

extern t_free_list	g_free_lists[];
extern t_area_list	g_area_list;

int				area__can_fit(t_area *a, size_t size)
{
	assert(a->size > a->cur_size);
	return (a->size - a->cur_size > size);
}

void			area__extend(t_area *a, size_t extention_size)
{
	assert(a->is_single_block == 0);
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
	block__log(b, "new\t");
	#endif
	return (b);
}

t_free_block	*area__deallocate_block(t_area *a, t_block *b)
{
	t_free_block	*fb;
	t_block			*next;

	assert(b->free == 0);
	next = BLOCK__NEXT(b);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__deallocate_prev(next);
	if (a->is_single_block)
	{
		area_list__remove(&g_area_list, a);
		return (NULL);
	}
	if (AREA__CUR_END(a) == (void*)BLOCK__NEXT(b))
	{
		area__deallocate_wilderness_block(a, b);
		return (NULL);
	}
	fb = free_block__deallocate(b);
	return (fb);
}

t_block			*area__allocate_free_block(t_area *a, t_free_block *fb)
{
	t_block	*b;
	t_block	*next;

	assert(fb->block.free);
	next = BLOCK__NEXT(&fb->block);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__allocate_prev(next);
	b = free_block__allocate(fb);
	return (b);
}

void			area__destroy_free_block(t_area *a, t_free_block *fb)//CHECKME: other things to do?
{
	t_free_list	*fl;
	t_block	*next;

	assert(fb->block.free);
	#ifdef LOG
	free_block__log(fb, "destroy");
	#endif
	fl = free_list__find(g_free_lists, fb->block.size);
	free_list__remove(fl, a, fb);
	next = BLOCK__NEXT(&fb->block);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__allocate_prev(next);
}

void			area__destroy_block(t_area *a, t_block *b)
{
	assert(AREA__CUR_END(a) == (void*)BLOCK__NEXT(b));
	assert(a->cur_size >= b->size + sizeof(t_block));
	a->cur_size -= b->size + sizeof(t_block);
	assert(a->cur_size >= sizeof(t_area));
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
