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

# define		N_FREE_LISTS 3
typedef struct	s_free_list
{
	size_t		min_size;
	t_fblock	*head;
}				t_free_list;

/*
**	core
*/

# define		MIN(a,b) ((a) < (b) ? (a) : (b))
# define		MAX(a,b) ((a) > (b) ? (a) : (b))
# define		ALLIGN(size,allign) (((size) + ((allign) - 1)) & ~((allign) - 1))
# define		MIN_BLOCK_SIZE ALLIGN((sizeof(struct s_free_list*) * 2), 8)
# define		MIN_AREA_SIZE(pgsz) ((pgsz) * 2)
# define		DATA(b) ((b) + sizeof(t_block))
# define		AREA_AVAILABLE_SIZE(a) ((a)->size - (a)->cur_size)

t_area			*new_area(size_t size);
t_area			*find_area_with_available_size(size_t size);
t_fblock		*find_free_block(size_t size);
t_block			*find_block(void *ptr);
void			free_list_insert();

#ifdef MALLOC_LOG

void			init_log(void);
void			malloc_log_new_block(t_block *block);
void			malloc_log_new_area(t_area *area);

#endif

/*
**	lib.c
*/

void			put_hex(int fd, size_t n);
void			put_dec(int fd, size_t n);
void			put_str(int fd, char *s);

/*
**	colors
*/

# define		BLOCK_HEADER	""
# define		BLOCK_DATA		""
# define		FREE_LIST_NODE	""
# define		AREA_HEADER		""
# define		AREA_BODY		""

#endif
