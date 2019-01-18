#include <malloc.h>
#include <shared.h>
#include <string.h>

#ifdef LOG
static inline void	realloc__log(void *ptr, size_t size)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	put_str(fd, "realloc(");
	put_hex(fd, (size_t)ptr, 1);
	put_str(fd, ", ");
	put_dec(fd, size);
	put_str(fd, ")\n");
}
#endif

extern t_area_list	g_area_list;

void	*realloc(void *ptr, size_t size)
{
	void				*new_ptr;
	t_block				*b;
	t_area				*a;

	#ifdef LOG
	realloc__log(ptr, size);
	#endif
	if (ptr == NULL)
		return (malloc(size));
	a = area_list__search(&g_area_list, area__find_in_range, ptr);
	if (a)
		b = area__search(a, block__find_address, ptr);
	if (a == NULL || b == NULL)
	{
		error__ptr_was_not_allocated("realloc", ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	memcpy(new_ptr, ptr, MIN(size, b->size));
	return (new_ptr);
}
