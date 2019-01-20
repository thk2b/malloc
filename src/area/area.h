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
# define AREA__IS_IN_BOUNDS(a, ptr) ((void*)(a) <= ((void*)(ptr)) && ((void*)(ptr)) < AREA__CUR_END(a))
# define AREA__HAS_FREE_BLOCK(a, i) ((i) < FL__N_FREE_LISTS && (void*)(a)->first_free_block[(i)] != NULL && (void*)(a)->last_free_block[(i)] != NULL)
# define AREA__HEADER_COLOR CYAN
# define AREA__REMAINING_COLOR WHITE

typedef struct		s_area
{
	struct s_area	*next;
	struct s_area	*prev;
	size_t			is_single_block:1;
	size_t			size:sizeof(size_t) * 8 - 1;
	size_t			cur_size;
	t_free_block	*first_free_block[FL__N_FREE_LISTS];
	t_free_block	*last_free_block[FL__N_FREE_LISTS];
}					t_area;

typedef int			(*t_area__search_fn)(t_block *block, void *ctx);
typedef int			(*t_area__count_fn)(t_block *block, void *ctx);
typedef void		(*t_area__foreach_fn)(t_block *block, size_t index, void *ctx);

void				area__extend(t_area *a, size_t extention_size);
t_block				*area__search(t_area *a, t_area__search_fn fn, void *ctx);
size_t				area__count_free_space_after(t_area *a, t_block *b, size_t until, t_free_block **last_encountered_fb);
size_t				area__count_free_space_before(t_area *a, t_block *b, size_t until);
void				area__foreach(t_area *a, t_area__foreach_fn fn, void *ctx);
t_block				*area__search_after(t_area *a, t_block *block, t_area__search_fn fn, void *ctx);
t_block				*area__search_before(t_area *a, t_block *block, t_area__search_fn fn, void *ctx);
t_block				*area__allocate_new_block(t_area *a, size_t size);
t_block				*area__allocate_free_block(t_area *a, t_free_block *fb);
void				area__destroy_free_block(t_area *a, t_free_block *fb);
t_free_block		*area__deallocate_block(t_area *a, t_block *block);
t_free_block		*area__coalesce(t_area *a, t_free_block *fb, size_t requested_size, t_free_block **last_encountered_adjacent_fb);
int					area__split_free_block(t_area *a, t_free_block *b, size_t target_size);

int					area__find_in_range(t_area *a, void *ctx);
int					area__find_has_free_block(t_area *a, void *ctx);

void				area__hexdump(t_area *a, size_t index, void *ctx);
void				area__show_alloc(t_area *a, size_t index, void *ctx);

# ifdef LOG
void				area__log(t_area *area, char *msg);
# endif

#endif
