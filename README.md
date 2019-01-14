# malloc
A malloc implementation

`Note: This is a first draft. The project is functional, but will be improved and optimized.`

# API
```c
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);
void	dump_mem(void);
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

- placement policy: first fit

- free blocks are held in explicit address-ordered segregated free lists

- adjacent free blocks are coallesed before additional memory is requested from the operating system
