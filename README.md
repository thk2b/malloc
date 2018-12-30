# malloc
A malloc implementation

`Note: This is a first draft. The project is functional, but will be improved and optimized.`

# API
```c
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);
```

# Usage & testing

To create the library:
```sh
make
```

To add the shared library as the system malloc library:
```sh
source scripts/inject.sh
```

To reset environment variables:
```sh
source scripts/reset.sh
```

# Implementation requirements

- Memory must be managed via `mmap(2)` and `mmunmap(2)`

- Pre-allocate 2 zones to satisfy at least 100 allocations:
  - small (1 to n bytes)
  - medium (n + 1 to m bytes)

If no free elements are found in the apropriate zone, the next is used.

- Large allocations are directly satisfied with `mmap`.

- Allocated memory must be properly alligned.

# Architecture

- `malloc` is a first-fit algorithm

- free blocks are held in an explicit free list

- `free` immediately coalleses neighboring free blocks

Memory is managed via two entities, `area`s, representing virtual memory pages, and `block`s, representing allocated blocks of memory.

# Implementation

Each area has its own free list.

```c
typedef struct	s_block
{
	size_t		size:1;
	size_t		size:sizeof(size_t) * 8 - 1;
}				t_block;

typedef struct	s_free_block
{
	t_block				*head;
	struct s_free_block	*prev;
	struct s_free_block	*next;
}				t_free_block;

typedef struct	s_area
{
	size_t			size;
	size_t			cur_size;
	t_free_block	*free_head;
	t_area			*next;
}				t_area;
```
