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

# Architecture

- Free blocks are stored in an adress-ordered linked list

- 3 free lists are used, one for each size class

- Free blocks are selected on a first fit basis

- Memory is defragmented at allocation size

# Further improvements

- [ ] Block checksums for fast freeing
