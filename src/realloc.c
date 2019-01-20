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

static void	*malloc_copy_free(t_block *b, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	memcpy(new_ptr, BLOCK__DATA(b), MIN(size, b->size));
	free(BLOCK__DATA(b));
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*b;
	t_block	*new_block;
	t_area	*a;

	#ifdef LOG
	realloc__log(ptr, size);
	#endif
	if (ptr == NULL)
		return (malloc(size));
	a = area_list__search(&g_area_list, area__find_in_range, ptr);
	if (a)
		b = area__search(a, block__find_address, ptr); //TODO: area__block_from_ptr
	if (a == NULL || b == NULL)
	{
		error__ptr_was_not_allocated("realloc", ptr);
		return (NULL);
	}
	if (b->size == size)
		return (ptr);
	if (size < b->size)
	{
		// area__split_block(a, b, size);
		return (ptr);
	}
	if ((new_block = area__coalesce_block(a, b, size)) == NULL)
		return (malloc_copy_free(b, size));
	return (BLOCK__DATA(new_block));
}
