/*
**	AreaList
**	Manages `mmaped(2)` memory regions
*/

#ifndef AREA_LIST_H
# define AREA_LIST_H
# include <area.h>

typedef struct	s_area_list
{
	t_area		*head;
	t_area		*tail;
	size_t		size;
}				t_area_list;

typedef t_area	*(*area_list__search_fn)(t_area *area, void *ctx);
t_area			*area_list__search_area(area_list__search_fn fn, void *ctx);

void			area_list__shift(t_area_list *al, t_area *a);
void			area_list__append(t_area_list *al, t_area *a);
t_area			*area_list__request_mem(t_area_list *al, size_t size);
int				area_list__release_mem(t_area_list *al, t_area *area);

#endif
