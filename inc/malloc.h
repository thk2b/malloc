#ifndef MALLOC_H
# define MALLOC_H
# include <stddef.h>

extern void	*malloc(size_t size);
extern void	*calloc(size_t count, size_t size);
extern void	free(void *ptr);
extern void	*realloc(void *ptr, size_t size);
extern void	show_alloc_mem(void);
extern void	dump_mem(void);

#endif
