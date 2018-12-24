#ifndef							FT_MALLOC_H
# define						FT_MALLOC_H

# include <sys/mman.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>

# define ALLIGN(size, allign)	(((size) + ((allign) - 1)) & ~((allign) - 1))
# define SET(addr, value)		((void*)(addr) = (value))

/*
**	exported API
*/

extern void		*malloc(size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		show_alloc_mem(void);

/*
**	block
*/

typedef struct	s_block
{
	size_t				size;
	struct s_block		*prev;

}				t_block;

# define B_DATA(b)				((void*)((char*)b + sizeof(t_block)))
# define B_BLOCK(ptr)			((t_block*)((char*)ptr - sizeof(t_block)))
# define B_NEXT(b)				((t_block*)((char*)B_DATA(b) + b->size))
# define B_PREV(b)				((b)->prev)
# define B_SIZE(b)				((b)->size & ~0x7)

# define B_FLAGS(b)				((b)->size & (SIZE_MAX ^ 0x7))
# define B_FLAG_FREE			0x1
# define B_FLAG_USED			0x2
# define B_FLAG_MMAPED			0x4

# define B_IS_FREE(b)			(FLAGS(b) & B_FLAG_FREE)
# define B_IS_USED(b)			(FLAGS(b) & B_FLAG_USED)
# define B_IS_MMAPED(b)			(FLAGS(b) & B_FLAG_MMAPED)

# define B_SET_FREE(b)			((b)->size |= B_FLAG_FREE)
# define B_SET_USED(b)			((b)->size |= B_FLAG_USED)
# define B_SET_MMAPED(b)		((b)->size |= B_FLAG_MMAPED)

/*
**	area
*/

typedef struct	s_area
{
	size_t		size;
}				t_area;

# define A_HEAD(a)				((t_block*)((char*)(a) + sizeof(t_area)))
# define A_NEXT(a)				((t_area*)((char*)(a) + sizeof(t_area) + (a)->size))
# define A_CAN_FIT(a, size)		((a)->size + sizeof(t_area) + sizeof(t_block) >= (size))

/*
**	zone
*/

#define N_ZONES					3
#define ZONE_S_SZ				32
#define ZONE_M_SZ				256

typedef struct	s_zone
{
	size_t		min_block_size;
	t_area		*head;
}				t_zone;

/*
**	core/block.c
*/

void			new_block(t_block *block, t_block *prev, size_t size);
void			append_block(t_block *a, t_block *b);
t_block			*find_block(t_area *head);
t_block			*split_block(t_block *block, size_t new_size);
t_block			*coalesce_block(t_block *block);

/*
**	core/area.c
*/

t_area			*new_area(size_t size);
void			append_area(t_area *a, t_area *b);

/*
**	core/zone.c
*/

t_zone			*get_zone(size_t size);

/*
**	lib/_.c
*/

void	ft_putstr(const char *str);
void	ft_putnbr(int n);
void	ft_putaddr(void *addr);


#endif
