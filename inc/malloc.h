#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# define MALLOC_LOG 1

/*
**	Exported API
*/

void			*malloc(size_t size);
void			*calloc(size_t count, size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			dump_mem(void);

/*
**	Block
**		Represents a single allocation
*/

typedef struct	s_block
{

}				t_block;

/*
**	Area
**		Represents a memoy area obtained via mmap
*/

typedef struct	s_area
{

}				t_area;


#endif
