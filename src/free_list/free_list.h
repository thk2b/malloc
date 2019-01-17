#ifndef FREE_LIST_H
# define FREE_LIST_H
# include <area.h>
# include <free_block.h>

# define FL__N_FREE_LISTS 3

typedef struct	s_free_list
{
	t_free_block	*head;
	size_t			min_size;
}				t_free_list;

typedef int		(*free_list__search_fn)(t_area *area, t_free_block *fb, void *ctx);

t_free_list		*free_list__find(t_free_list **fls, size_t size);
t_free_block	*free_list__search(t_free_list *fl, free_list__search_fn fn, void *ctx);
void			free_list__insert(t_free_list *fl, t_area *area, t_free_block *fb);
void			free_list__remove(t_free_list *fl, t_area *area, t_free_block *fb);
void			free_list__range(t_free_list *fl, t_area *area, t_free_block *fb);

#endif
