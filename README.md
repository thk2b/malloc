# malloc
A malloc implementation

# API
```c
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);
```

# requirements

- Memory must be managed via `mmap(2)` and `mmunmap(2)`

- Pre-allocate 2 zones to satisfy at least 100 allocations:
  - small (1 to n bytes)
  - medium (n + 1 to m bytes)

If no free elements are found in the apropriate zone, the next is used.

- Large allocations are directly satisfied with `mmap`.

# architecture

- `malloc` is a first-fit algorithm

- `free` immediately coalleses neighboring free blocks

Memory is managed via two entities, `page`s, representing virtual memory pages, and `block`s, representing allocated blocks of memory.

Each zone is a set of pages. If a zone becomes fully allocated, we allocate additional pages.

# implementation

`page`s are a singly-linked list with a reference to its first `block`. `block`s are a doubly linked list, and contain their size and free-status.

```c
# define BLK_SZ sizeof(t_block)
# define IS_FREE(block) (block->data == NULL)

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			size;
	void			*data; //FIXME: replace with block+sizeof(t_block)?
}					t_block;

typdef struct		s_page
{
	struct s_page	*next;
	t_block			*head;
}					t_page;
```

We store pointers to the 3 zones.

```c
# define ZONE_S_SZ  16
# define ZONE_M_SZ  64

typedef struct	s_zones
{
	t_page	*s;
	t_page	*m;
	t_page	*l;
}				t_zones;

t_zones *g_zones = { NULL, NULL, NULL };
```

We initialize the zones on the first call to `malloc`.

```c
//TODO: implement
```
Two search operations are defined over the pages:

- To find a free block of at least a certain size

```c
t_page *get_zone(t_zones *zones, size_t size)
{
	if (size < ZONE_S_SZ)
		return (zones->s);
	if (size < ZONE_M_SZ)
		  return (zones->m);
	return (zones->l);
}

inline t_block	*find_free_block_in_page(t_page page, size_t size)
{
	t_block *block;

	block = page->head;
	while (block)
	{
		if (IS_FREE(block) && block->size >= size)
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_block *find_free_block(t_zone *zone, size_t)
{
	t_page	*page;
	t_block	*block;

	page = get_zone(zone);
	block = NULL;
	while (page && (block = get_free_block(page, size)) == NULL)
		page = page->next;
	return (block);
```

- Finding an allocated block correstonding to an address. Since we dont know the allocated size, we iterate over all paes of all zones.

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
