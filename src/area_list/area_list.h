/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:21:04 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 10:39:20 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	AreaList
**	Manages `mmaped(2)` memory regions
**	Is a linked list of areas
*/

#ifndef AREA_LIST_H
# define AREA_LIST_H
# include <shared.h>

typedef struct	s_area_list
{
	t_area		*head;
	t_area		*tail;
}				t_area_list;

typedef int		(*t_area_list__search_fn)(t_area *area, void *ctx);
typedef void	(*t_area_list__foreach_fn)(
	t_area *area, size_t index, void *ctx);

t_area			*area_list__search(t_area_list *al,
	t_area_list__search_fn fn, void *ctx);
t_area			*area_list__search_around(t_area *a,
	t_area_list__search_fn fn, void *ctx);
t_area			*area_list__search_from(t_area *start,
	t_area_list__search_fn fn, void *ctx);
void			area_list__foreach(t_area_list *al,
	t_area_list__foreach_fn fn, void *ctx);
t_area			*area_list__insert(t_area_list *al, t_area *a);
void			area_list__remove(t_area_list *al, t_area *a);
t_area			*area_list__request_mem(t_area_list *al, size_t size);
int				area_list__release_mem(t_area_list *al, t_area *a);
void			area_list__show_alloc_mem(t_area_list *al);

# ifdef LOG

void			area_list__log(t_area_list *al, char *msg);

# endif

#endif
