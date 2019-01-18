#include <malloc.h>
#include <shared.h>

extern t_free_list	g_free_lists[];
extern t_area_list	g_area_list;

#ifdef LOG
static inline void	malloc__log(size_t size)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	put_str(fd, "malloc(");
	put_dec(fd, size);
	put_str(fd, ")\n");
}
#endif

extern void			*malloc(size_t size)
{
	/* Stage 2
	t_free_list		*fl;
	t_free_block	*fb;
	*/
	t_area			*a;
	t_block			*b;

	size = MAX(ALLIGN(size, 8), FREE_BLOCK__MIN_SIZE);
	#ifdef LOG
	malloc__log(size);
	# endif
	/*	Stage 2
	fl = free_list__find(g_free_lists, size);
	fb = free_list__search(fl, &a, free_list__first_fit, (void*)&size);
	if (fb)
		b = area__allocate_free_block(a, fb);
	else */ if ((a = area_list__request_mem(&g_area_list, size)))
		b = area__allocate_new_block(a, size);
	else
		return (NULL);
	return (BLOCK__DATA(b));
}

#ifdef TEST

#endif
