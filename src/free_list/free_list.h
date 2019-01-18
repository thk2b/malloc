/*
**	FreeList
**	Represents a sequence of blocks, of at lease a certain size, which are available for reuse
**	Is an address ordered doubly linked list of free blocks
*/

#ifndef FREE_LIST_H
# define FREE_LIST_H
# include <shared.h>

# define FL__N_FREE_LISTS 3

typedef struct	s_free_list
{
	t_free_block	*head;
	size_t			min_size;
}				t_free_list;

typedef int		(*free_list__search_fn)(t_area *area, t_free_block *fb, void *ctx);

t_free_list		*free_list__find(t_free_list *fls, size_t size);
t_free_block	*free_list__search(t_free_list *fl, t_area **areap, free_list__search_fn fn, void *ctx);
void			free_list__insert(t_free_list *fl, t_area *area, t_free_block *fb);
void			free_list__remove(t_free_list *fl, t_area *area, t_free_block *fb);
void			free_list__remove_range(t_free_list *fl, t_area *area, t_free_block *from, t_free_block *to);
int				free_list__first_fit(t_area *area, t_free_block *fb, void *ctx);
void			free_list__hexdump(t_free_list *b);
# ifdef MALLOC_LOG
void			free_list_log(t_free_list *fl, char *msg);
# endif

int				free_list__find_first_fit(t_block *block, void *ctx);
int				free_list__find_first_fit_coalesce(t_block *block, void *ctx);
int				free_list__find_first_fit_split(t_block *block, void *ctx);

#endif
