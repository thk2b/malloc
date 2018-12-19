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

	This is a constant time operation but is ineficient because free blocks might be coallesed, then split soon thereafter.

Memory is managed via two entities, `page`s, representing virtual memory pages, and `block`s, representing allocated blocks of memory.

Each zone is a set of pages. If a zone becomes fully allocated, we allocate additional pages.

# Implementation

`page`s are a singly-linked list with a reference to its first `block`, and a `size` which muct be a multiple of `getpagesize()`. `block`s are a doubly linked list, and contain their size and free-status.

```c
# define BLK_SZ sizeof(t_block)
# define IS_FREE(block) (block->data == NULL)
# define BLK_DATA(b) (b + BLK_SZ)

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
}					t_block;

typdef struct		s_page
{
	struct s_page	*next;
	size_t			size;
	size_t			min_block_size;
	t_block			*head;
}					t_page;
```

We store pointers to the 3 zones.

```c
# define ZONE_S_SZ  16
# define ZONE_M_SZ  64

t_zones	g_zones[] = {
	{NULL, 0, 0, NULL},
	{NULL, 0, ZONE_S_SZ + 1, NULL},
	{NULL, 0, ZONE_M_SZ + 1, NULL},
	NULL
}

```

To allocate memory, we first find the zone with the largest minimum-size that can accomodate the given size.

```c
t_page *get_zone(t_zones *zones, size_t size)
{
	size_t	i;

	i = 1;
	while (zones[i])
		if (size < zones[i]->min->block_size)
			return (zones[i - 1]);
		else
			i++;
	return (zones[i - 1]);
}
```

Then, we find a free block in that set of pages.

To add a free block in a page, find the last block and add a new free one after it. If there is no free block, we append a new one to the page and return it. If the page is full, we allocate and append a newly-mapped page.

```c

t_page	*append_page(t_page *page)
{
	//TODO: implement
}

void	init_block(t_block *block, t_block *prev)
{
	block->prev = block;
	block->next = prev;
	block->data = NULL;
	block->size = 0;
}

t_block	append_free_block(t_page *page)
{
	//TODO: implement
	t_block	*block;
	t_block	new_block;

	block = page->head;
	while (block && block->next)
		block = block->next;
	if (block == NULL)
		return (NULL);
	init_block(&new_block, block)
	(char*)block->data + block->size = new_block;
	block->next = (void*)((char*)block->data + block->size);
	reutrn ((void*)((char*)block->data + block->size));
}

inline t_block	*get_free_block_in_page(t_page page, size_t size)
{
	t_block *block;

	block = page->head;
	while (block)
	{
		if (IS_FREE(block) && block->size >= size)
			return (block);
		block = block->next;
	}
	if ((block = append_free_block(page))
		return (block);
	if ((page = append_page(page) == NULL)
		return (NULL);
	return (get_free_block_in_page(page));
}

t_block	*get_free_block(t_zone *zone, size_t)
{
	t_page	*page;
	t_block	*block;

	page = get_zone(zone);
	block = NULL;
	while (page && (block = get_free_block_in_page(page, size)) == NULL)
		page = page->next;
	return (block);
```

Then, we set the data in the block and return the address.
Once we find a free block, we return the address of the block's data space. If the block is larger than the requested space, the remainder of the block becomes a new free block. This is a necesary tradeof for our first-fit algorithm. A best-fit algorithm would not suffer this flaw, but at the expence of execution speed. This causes blocks to become smaller and smaller. One issue is that the `medium` zone might end up storing blocks of size `small`, thus will never be allocated. To prevent this, we never split a block smaller than the minimum size of the zone.

```c
void	*malloc(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	zone = get_zone(g_zones, size);
	block = get_free_block(zone, size);
	if (block->size > size && block->size - size > zone->min_size)
		split_block(block);
	block->size = size;
	return (block->data);
}
```

To free a pointer, we first find an allocated block correstonding to the given data address. Since we dont know the allocated size, we iterate over all pages of all zones.

```c
inline t_block	*find_block_in_page(t_page *page, void* ptr)
{
	t_block *block;

	block = page->start;
	while (block)
	{
		if (block->data == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_block			*find_block(t_zone *zone, size_t)
{
	t_page	*page;
	t_block	*block;

	page = get_zone(zone);
	block = NULL;
	while (page && (block = find_block(page, size)) == NULL)
		page = page->next;
	return (block);
```

Then, we set the data to indicate a free block. Finally, we coalesce neighboring blocks into one.

```c
void	coalesce(t_block *block)
{
	//TODO: implement
}

void	free(void *ptr)
{
	t_block	*block;

	if ((block = find_block(ptr)) == NULL)
		return (free_error("pointer was not allocated"));
	block->data = NULL;
	coalesce(block);
}
```
