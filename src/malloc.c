#include <malloc.h>
#include <shared.h>

extern t_free_list	g_free_lists[];
extern t_area_list	*g_area_list;

static inline	malloc__log(size_t size)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	put_str(g_log_fd, "malloc(");
	put_dec(g_log_fd, size);
	put_str(g_log_fd, ")");
}

extern void	*malloc(size_t size)
{
	t_free_list		*fl;
	t_area			*a;
	t_free_block	*fb;
	t_block			*b;

	size = ALLIGN(size, 8);
	#ifdef LOG
	malloc__log(size);
	# endif
	fl = free_list__find(g_free_lists, size);
	fb = free_list__search(fl, &a, free_list__first_fit, (void*)&size);
	if (fb)
		b = area__allocate_free_block(a, fb);
	else if ((a = area_list__request_mem(g_area_list, size)))
		b = area__allocate_new_block(a, size);
	else
		return (error__no_mem());
	return (block__data(b));
}

#ifdef TEST



#endif
