# malloc
A malloc implementation

# API
```c
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);
```

# Requirements

- Memory must be managed via `mmap(2)` and `mmunmap(2)`

- Pre-allocate 2 zones to satisfy at least 100 allocations:
  - small (1 to n bytes)
  - medium (n + 1 to m bytes)

If no free elements are found in the apropriate zone, the next is used.

- Large allocations are directly satisfied with `mmap`.

- Allocated memory must be properly alligned.

# Architecture

- `malloc` is a first-fit algorithm

- `free` immediately coalleses neighboring free blocks

Memory is managed via two entities, `page`s, representing virtual memory pages, and `block`s, representing allocated blocks of memory.

# Usage & testing

# Implementation

This is a summary of my first draft implementation of the library.

`page`s are a singly-linked list with a reference to its first `block`, and a `size` which must be a multiple of `getpagesize()`. `block`s are a doubly linked list, and contain their size and free-status.

In this draft implementation, pointers to `next` and `data` are explicit. They can be made implicit with pointer arithmetic in order to reduce memory overhead.

```c
// ft_malloc.h
# define IS_FREE(block) (block->data == NULL)

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
	void			*data;
}					t_block;

typedef struct		s_page
{
	struct s_page	*next;
	size_t			size;
	size_t			cur_size;
	size_t			min_block_size;
	t_block			*head;
}					t_page;
```

We store empty header-pages for each zones. We define pages with 0 size and a minimum size, which additional pages will inherit. When satisfying the first allocation in each zone, a new page will be created with size ` PAGES_PER_MAP * getpagesize()`.

```c
// core/zones.c
t_page	g_zones[] = {
	{NULL, 0, 0, 0, NULL},
	{NULL, 0, 0, ZONE_S_SZ + 1, NULL},
	{NULL, 0, 0, ZONE_M_SZ + 1, NULL},
};
```

To allocate memory, we first find the zone with the largest minimum-size that can accomodate the given size.

```c
// core/zones.c
t_page *get_zone(t_zones *zones, size_t size)
{
	extern t_page	g_zones[];
	size_t	i;

	i = 1;
	while (i < NZONES && size > g_zones[i].min_block_size)
		i++;
	return (g_zones + (i - 1));
}
```

This is how `malloc` is implemented. We simply find the first free block, in the apropriate zone, large enough to satisfy the request and possibly split the block into two (TODO). This might cause blocks to become smaller and smaller, so the `medium` zone might end up storing blocks of size `small`, thus will never be allocated. To prevent this, we never split a block smaller than the minimum size of the zone. We return a pointer to the data atrribute of the block.

```c
// malloc.c
extern void	*malloc(size_t size)
{
	t_page			*page;
	t_block			*block;

	size = ALLIGN(size, 8);
	page = get_zone(size);
	if ((block = get_free_block(page, size)) == NULL)
		return (NULL);
	if (block->size > size && block->size - size > page->min_block_size)
		split_block(block);
	return (block->data);
}
```

To find a free block, we traverse each page in the zone. If a previously freed block exists, update its metadata and return it. Otherwise, we add a new block to the page. If there is no room left on the page, we allocate a new page.

```c
// core/get_free_block.c
static inline t_block
				*get_free_block_in_page(t_page *page, size_t size)
{
	t_block	*block;
	t_block	*prev;

	block = page->head;
	prev = NULL;
	while (block)
	{
		if (IS_FREE(block) && block->size >= size)
		{
			block->data = (void*)((char*)block + sizeof(t_block));
			block->size = size;
			return (block);
		}
		prev = block;
		block = block->next;
	}
	return (append_new_block(page, prev, size));
}

t_block			*get_free_block(t_page *zone, size_t size)
{
	t_page	*page;
	t_page	*prev;
	t_block	*block;

	page = zone;
	block = NULL;
	while (page)
	{
		if ((block = get_free_block_in_page(page, size)))
			return (block);
		prev = page;
		page = page->next;
	}
	if ((page = append_page(prev, size)) == NULL)
		return (NULL);
	return (get_free_block_in_page(page, size));
}
```

Creating a block is a matter of adding a block after the last one of a page. The memory overhead of this implementation is obvious, there is more metadata than necessary.

```c
// core/block.c
void	init_block(t_block *block, t_block *prev, size_t size)
{
	block->prev = prev;
	block->next = NULL;
	block->data = (void*)((char*)block + sizeof(t_block));
	block->size = size;
	block->next = NULL;
	if (prev)
		prev->next = block;
}

t_block			*append_new_block(t_page *page, t_block *prev, size_t size)
{
	t_block		*new_block;
	size_t		new_page_size;

	new_page_size = page->cur_size + sizeof(t_block) + size;
	if (page->cur_size + new_page_size >= page->size)
		return (NULL);
	new_block = prev ?
		(t_block*)((char*)prev + sizeof(t_block) + prev->size) : (t_block*)((char*)page + sizeof(t_page));
	init_block(new_block, prev, size);
	if (page->head == NULL)
		page->head = new_block;
	page->cur_size = new_page_size;
	return (new_block);
}
```

To add a new page, we use `mmap` and initialize the metadata.

```c
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
	size_t	total_size;

	pg_size = getpagesize();
	alloc_size = pg_size * PAGES_PER_MAP;
	total_size = size + sizeof(t_page);
	if (total_size >= alloc_size)
		alloc_size = ALLIGN(total_size + sizeof(t_block), pg_size);
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
	init_page((t_page*)data, alloc_size - sizeof(t_page), page->min_block_size);
	page->next = (t_page*)data;
	return (page->next);
}
```

Free is implemented as follows. We Find the block with the asociated data pointer, and mark it as available. If a newly-freed block has free neighbors, they are merged together to reduce memory frgmentation.	This is a constant time operation but is ineficient because free blocks might be coallesed, then split soon thereafter.

```c
// free.c
static inline void	merge_blocks(t_block *a, t_block *b)
{
	a->size += b->size + sizeof(t_block);
	a->next = b->next;
	if (b->next)
		b->next->prev = a;
}

static inline void	coalesce(t_block *block)
{
	if (block->prev && IS_FREE(block->prev))
		merge_blocks(block->prev, block);
	if (block->next && IS_FREE(block->next))
		merge_blocks(block, block->next);
}

extern void			free(void *ptr)
{
	t_block	*block;

	if (ptr == NULL)
		return ;
	if ((block = find_block(ptr)) == NULL)
	{
		// write(2, "pointer was not allocated\n", 27);
		return ;
	}
	block->data = NULL;
	coalesce(block);
}
```

Finally, realloc is implemented as follows.
We allocate a new block, copy the data, and free the old block. This is ineficient: if there is no `next` block, and the page has sufficient space, just resize the block.

```c
extern void	*realloc(void *ptr, size_t size)
{
	char	*new_ptr;
	t_block	*block;

	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	if (ptr == NULL)
		return (new_ptr);
	if ((block = find_block(ptr)) == NULL)
		return (new_ptr);
	memmove(new_ptr, ptr, MIN(block->size, size));
	free(ptr);
	return (new_ptr);
}
```
