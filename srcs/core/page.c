#include <ft_malloc.h>

static void	init_page(t_page *page, size_t max_size, size_t min_block_size)
{
	page->next = NULL;
	page->size = max_size;
	page->cur_size = 0;
	page->min_block_size = min_block_size;
	page->head = NULL;
}

t_page	*append_page(t_page *page, size_t size)
{
	void	*data;
	size_t	pg_size;
	size_t	alloc_size;

	pg_size = getpagesize();
	alloc_size = pg_size * PAGES_PER_MAP;
	if (size + sizeof(t_block) >= alloc_size)
		alloc_size = ALLIGN(size, pg_size);
	data = mmap(
		NULL,
		alloc_size,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,
		-1, 0
	);
	if (data == MAP_FAILED)
	{
		write(2, "MAP_FAILED\n", 11);
		return (NULL);
	}
	init_page((t_page*)data, alloc_size, page->min_block_size);
	page->next = (t_page*)data;
	return (page->next);
}
