/*
**	Area
**	Manages the content of allocated memory regions
**	Contains a set of adjacent blocks
*/

#ifndef AREA_H
# define AREA_H
# include <shared.h>

# define AREA__AVAILABLE_SIZE(a) ((a)->size - (a)->cur_size)
# define AREA__CAN_FIT(a, s) ((AREA__AVAILABLE_SIZE(a) >= (s)))
# define AREA__CUR_END(a) ((void*)((char*)(a) + (a)->cur_size))
# define AREA__IS_END(a, ptr) ((void*)((char*)(a) + (a)->size) == (void*)(ptr))
# define AREA__HEAD(a) ((t_block*)((char*)a + sizeof(t_area)))
# define AREA__END(a) ((void*)((char*)(a) + (a)->size))
# define AREA__IS_IN_BOUNDS(a, ptr) ((void*)(a) <= ((void*)ptr) && ((void*)ptr) < AREA__END(a))
# define AREA__HEADER_COLOR CYAN
# define AREA__REMAINING_COLOR WHITE

typedef struct		s_area
{
	struct s_area	*next;
	struct s_area	*prev;
	size_t			is_single_block:1;
	size_t			size:sizeof(size_t) * 8 - 1;
	size_t			cur_size;
}					t_area;

typedef int			(*t_area__search_fn)(t_block *block, void *ctx);
typedef void		(*t_area__foreach_fn)(t_block *block, size_t index, void *ctx);

// int					area__is_in_bounds(t_area *a, void *addr);
// int					area__is_head(t_area *a, void *addr);
// int					area__is_tail(t_area *a, void *addr);
int					area__is_end(t_area *a, void *addr);
void				area__extend(t_area *a, size_t extention_size);
t_block				*area__search(t_area *a, t_area__search_fn fn, void *ctx);
void				area__foreach(t_area *a, t_area__foreach_fn fn, void *ctx);
t_block				*area__search_after(t_area *a, t_block *block, t_area__search_fn fn, void *ctx);
t_block				*area__search_before(t_area *a, t_block *block, t_area__search_fn fn, void *ctx);
t_block				*area__allocate_new_block(t_area *a, size_t size);
t_block				*area__allocate_free_block(t_area *a, t_free_block *fb);
t_free_block		*area__deallocate_block(t_area *a, t_block *block);
t_free_block		*area__split_free_block(t_area *a, t_free_block *b, size_t target_size);
t_free_block		*area__extend_free_block(t_area *a, t_free_block *b, size_t target_size);

int					area__find_in_range(t_area *a, void *ctx);

void				area__hexdump(t_area *a, size_t index, void *ctx);
void				area__show_alloc(t_area *a, size_t index, void *ctx);

#ifdef LOG
void				area__log(t_area *area, char *msg);
#endif

// int					area__search_first_fit(t_block *block, void *ctx);
// int					area__search_first_fit_coalesce(t_block *block, void *ctx);
// int					area__search_first_fit_split(t_block *block, void *ctx);

#endif
