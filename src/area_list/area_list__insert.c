/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_list__insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:26:45 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:28:40 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

static int				area__find_prev(t_area *a, void *ctx)
{
	return ((void*)a < ctx && (a->next == NULL || (void*)a->next > ctx));
}

static t_area			*area_list__init(t_area_list *al, t_area *a)
{
	#ifdef LOG
	area__log(a, "new\t");
	#endif
	al->head = a;
	al->tail = a;
	return (a);
}

static inline t_area	*dumb(t_area *prev, t_area *a)
{
	area__extend(prev, a->size);
	return (prev);
}

t_area					*area_list__insert(t_area_list *al, t_area *a)
{
	t_area	*prev;
	t_area	*next;

	if (al->head == NULL)
		return (area_list__init(al, a));
	prev = area_list__search(al, area__find_prev, a);
	next = prev ? prev->next : al->head;
	if (prev && prev->is_single_block == 0
		&& a->is_single_block == 0 && AREA__IS_END(prev, a))
			return (dumb(prev, a));
	if (prev == NULL)
		al->head = a;
	else if (prev->next == NULL)
		al->tail = a;
	if (prev)
		prev->next = a;
	a->prev = prev;
	if (next)
		next->prev = a;
	a->next = next;
	#ifdef LOG
	area__log(a, a->is_single_block ? "new single" : "new\t");
	#endif
	return (a);
}
