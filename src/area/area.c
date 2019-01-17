#include <shared.h>
#include <assert.h>

int			area__can_fit(t_area *a, size_t size)
{
	assert(a->size > a->cur_size);
	return (a->size - a->cur_size > size);
}

void		area__extend(t_area *a, size_t extention_size)
{
	a->size += extention_size;
	#ifdef LOG
	area__log(a, "extended");
	#endif
}

t_block		*area__allocate_new_block(t_area *a, size_t size)
{
	t_block	*b;

	assert(area__can_fit(a, size + sizeof(t_block)));
	b = block__allocate((void*)((char*)a + a->cur_size), size);
	a->cur_size += size + sizeof(t_block);
	#ifdef LOG
	block__log(b, "new block");
	#endif
	return (b);
}

void		area__foreach(t_area *a, t_area__foreach_fn fn, void *ctx)
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

t_block		*area__search(t_area *a, t_area__search_fn fn, void *ctx)
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

void		area__hexdump(t_area *a, size_t index, void *ctx)
{
	UNUSED(index);
	UNUSED(ctx);
	hexdump((void*)a, sizeof(t_area), AREA__HEADER_COLOR);
	area__foreach(a, block__hexdump, NULL);
	hexdump((void*)AREA__CUR_END(a), AREA__AVAILABLE_SIZE(a), AREA__REMAINING_COLOR);
	put_str(1, a->next ? "\n    ⋮" : "\n");
}

void		area__show_alloc(t_area *area, size_t index, void *ctx)
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
void		area__log(t_area *a, char *msg)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	log__line_count(fd);
	put_str(fd, "area\t");
	put_hex(fd, (size_t)a, 1);
	put_str(fd, "\t");
	put_dec(fd, a->size);
	put_str(fd, "\t");
	put_str(fd, msg);
	put_str(fd, "\n");
}
#endif
