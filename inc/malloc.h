#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# define MALLOC_LOG 1

/*
**	Exported API
*/

extern void		*malloc(size_t size);
extern void		*calloc(size_t count, size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		show_alloc_mem(void);
extern void		dump_mem(void);

/*
*	Block
**		Represents a single allocation
*/

typedef struct	s_block
{
	size_t		free:1;
	size_t		size:sizeof(size_t) - 1;
}				t_block;

/*
**	Free block
*/

typedef struct	s_fblock
{
	t_block			block;
	struct s_fblock	*prev;
	struct s_fblock	*next;
}				t_fblock;

/*
**	Area
**		Represents a memoy area obtained via mmap
*/

typedef struct	s_area
{
	size_t			size;
	size_t			cur_size;
	struct s_area	*next;
}				t_area;

typedef struct	s_free_list
{
	size_t		min_size;
	t_block		*head;
}				t_free_list;

/*
**	core
*/

t_fblock		*find_free_block(size_t size);
t_block			*find_block(void *ptr);
void			free_list_insert()

#endif
