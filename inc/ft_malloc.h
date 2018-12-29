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
# define SET(addr, value)		((void*)(addr) = (value))
# define MIN(a, b)				((a) < (b) ? (a) : (b))

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
**	first byte of size contains flags
*/

typedef struct	s_block
{
	size_t				size;
	struct s_block		*prev;

}				t_block;

# define B_DATA(b)				((void*)((char*)b + sizeof(t_block)))
# define B_BLOCK(ptr)			((t_block*)((char*)ptr - sizeof(t_block)))
# define B_NEXT(b)				((t_block*)((char*)B_DATA(b) + B_SIZE(b)))
# define B_PREV(b)				((b)->prev)
# define B_FLAGS(b)				((b)->size & 0xF)

# define B_SIZE(b)				((b)->size >> (4))
// works on other-endian machines?
# define B_SET_SIZE(b, s)		((b)->size = (B_FLAGS(b) | (s) << 4))
# define B_FLAG_FREE			0x1
# define B_FLAG_MMAPED			0x2

# define B_IS_USED(b)			(B_FLAGS(b) & B_FLAG_FREE)
# define B_IS_FREE(b)			(!(B_IS_USED(b)))
# define B_IS_MMAPED(b)			(B_FLAGS(b) & B_FLAG_MMAPED)

# define B_SET_FREE(b)			((b)->size ^= B_FLAG_FREE)
# define B_SET_USED(b)			((b)->size |= B_FLAG_FREE)
# define B_SET_MMAPED(b)		((b)->size |= B_FLAG_MMAPED)

/*
**	area
*/

typedef struct	s_area
{
	size_t			size;
	size_t			cur_size;
	struct s_area	*next;
}				t_area;

# define A_HEAD(a)				((t_block*)((char*)(a) + sizeof(t_area)))
# define A_NEXT(a)				((a)->next)
# define A_CAN_FIT(a, s)		(((a)->cur_size + sizeof(t_area) + (s)) < (a)->size)
# define A_CUR_END(a)			((void*)((char*)A_HEAD(a) + (a)->cur_size))
# define A_END(a)				((void*)((char*)A_HEAD(a) + (a)->size))

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

void			new_block(t_block *block, size_t size, t_block *prev);
void			append_block(t_block *a, t_block *b);
t_block			*find_free_block(t_area *head, size_t size);
t_block			*find_block(void *data_ptr, t_area **area);
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
