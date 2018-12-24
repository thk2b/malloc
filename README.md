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

- `free` immediately coalleses neighboring free blocks

Memory is managed via two entities, `page`s, representing virtual memory pages, and `block`s, representing allocated blocks of memory.

# Implementation

This is a summary of my first draft implementation of the library.

`page`s are a singly-linked list with a reference to its first `block`, and a `size` which must be a multiple of `getpagesize()`. `block`s are a doubly linked list, and contain their size and free-status.

In this draft implementation, pointers to `next` and `data` are explicit. They can be made implicit with pointer arithmetic in order to reduce memory overhead.
