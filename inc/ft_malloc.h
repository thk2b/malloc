#ifndef							FT_MALLOC_H
# define						FT_MALLOC_H
// #define LIBFT_MALLOC_LOG

# include <sys/mman.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>

# define PAGES_PER_MAP			2
# define ALLIGN(size, allign)	(((size) + ((allign) - 1)) & ~((allign) - 1))
# define MIN(a, b)				((a) < (b) ? (a) : (b))
# define MAX(a, b)				((a) > (b) ? (a) : (b))

/*
**	exported API
*/

extern void		*malloc(size_t size);
extern void		*calloc(size_t count, size_t size);
extern void		free(void *ptr);
extern void		*realloc(void *ptr, size_t size);
extern void		show_alloc_mem(void);

/*
**	block
*/

typedef struct	s_block
{
	size_t		used:1;
	size_t		size:63;
	// size_t		size:sizeof(size_t) * 8 - 1;
}				t_block;

typedef struct	s_free_block
{
	size_t		used:1;
	size_t		size:63;
	struct s_free_block	*prev;
	struct s_free_block	*next;
}				t_free_block;

# define B_DATA(b)				((void*)((char*)b + sizeof(t_block)))
# define B_NEXT(b)				((t_block*)((char*)(b) + sizeof(t_block) + (b)->size))

/*
**	area
*/

typedef struct	s_area
{
	size_t			size;
	size_t			cur_size;
	struct s_area	*next;
	t_free_block	*free_head;
}				t_area;

# define A_HEAD(a)				((t_block*)((char*)(a) + sizeof(t_area)))
# define A_CAN_FIT(a, s)		(((a)->cur_size + sizeof(t_area) + (s)) < (a)->size)
# define A_CUR_END(a)			((void*)((char*)(a) + (a)->cur_size + sizeof(t_area)))
# define A_END(a)				((void*)((char*)(a) + (a)->size))

/*
**	zone
*/

#define N_ZONES					3
#define ZONE_S_SZ				64
#define ZONE_M_SZ				256

typedef struct	s_zone
{
	size_t		min_block_size;
	t_area		*head;
}				t_zone;

/*
**	core/block.c
*/

void			new_block(t_block *block, size_t size);
void			merge_blocks(t_block *a, t_block *b,
	t_free_block *prev_free_block, t_area *area);
t_block			*find_free_block(t_area *head, size_t size);
t_block			*find_block(void *data_ptr, t_area **area, t_free_block **last_free_block);
t_block			*split_block(t_block *block, size_t new_size);
void			coalesce_block(t_block *block, t_area *area);

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

size_t	ft_strlen(const char *str);
void	ft_putstr(const char *str);
void	ft_putnbr(int n);
void	ft_putaddr(void *addr);


#endif
