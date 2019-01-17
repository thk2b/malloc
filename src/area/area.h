/*
**	Area
**	Manages the content of allocated memory regions
**	Contains a set of adjacent blocks
*/

#ifndef AREA_H
# define AREA_H
# include <shared.h>

typedef struct		s_area
{
	struct s_area	*next;
	struct s_area	*prev;
	size_t			size;
	size_t			cur_size;
}					t_area;

typedef t_area		*(*area__search_fn)(t_block *block, void *ctx);

int					area__is_in_bounds(t_area *a, void *addr);
int					area__is_head(t_area *a, void *addr);
int					area__is_tail(t_area *a, void *addr);
int					area__can_fit(t_area *a, size_t size);
t_block				*area__search(t_area *a, area__search_fn fn, void *ctx);
t_block				*area__search_after(t_area *a, t_block *block, area__search_fn fn, void *ctx);
t_block				*area__search_before(t_area *a, t_block *block, area__search_fn fn, void *ctx);
t_block				*area__allocate_new_block(t_area *a, size_t size);
t_block				*area__allocate_free_block(t_area *a, t_free_block *fb);
t_block				*area__deallocate_block(t_area *a, size_t size);
t_free_block		*area__split_free_block(t_area *a, t_free_block *b, size_t target_size);
t_free_block		*area__extend_free_block(t_area *a, t_free_block *b, size_t target_size);

// int					area__search_first_fit(t_block *block, void *ctx);
// int					area__search_first_fit_coalesce(t_block *block, void *ctx);
// int					area__search_first_fit_split(t_block *block, void *ctx);

#endif
