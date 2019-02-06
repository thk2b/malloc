/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_list__search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:22:36 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:34:22 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

t_area				*area_list__search(t_area_list *al,
	t_area_list__search_fn fn, void *ctx)
{
	t_area	*a;

	a = al->head;
	while (a)
	{
		if (fn(a, ctx))
			return (a);
		a = a->next;
	}
	return (NULL);
}

static inline void	dumb(char direction,
	t_area **right, t_area **left, t_area **cur)
{
	if (*right == NULL)
	{
		*cur = *left;
		*left = (*left)->prev;
	}
	else if (*left == NULL)
	{
		*cur = *right;
		*right = (*right)->next;
	}
	else if (direction == 0)
	{
		*cur = *left;
		*left = (*left)->prev;
	}
	else if (direction == 1)
	{
		*cur = *right;
		*right = (*right)->next;
	}
}

t_area				*area_list__search_around(t_area *a,
	t_area_list__search_fn fn, void *ctx)
{
	char	direction;
	t_area	*left;
	t_area	*right;
	t_area	*cur;

	cur = a;
	left = a->prev;
	right = a->next;
	direction = 0;
	while (left || right)
	{
		dumb(direction, &right, &left, &cur);
		if (cur == NULL)
			break ;
		assert(cur != a);
		direction = !direction;
		if (fn(cur, ctx))
			return (cur);
	}
	return (NULL);
}

t_area				*area_list__search_from(t_area *start,
	t_area_list__search_fn fn, void *ctx)
{
	t_area	*a;

	a = start;
	while (a)
	{
		if (fn(a, ctx))
			return (a);
		a = a->next;
	}
	return (NULL);
}

void				area_list__foreach(t_area_list *al,
	t_area_list__foreach_fn fn, void *ctx)
{
	t_area	*a;
	size_t	index;

	index = 0;
	a = al->head;
	while (a)
	{
		fn(a, index++, ctx);
		a = a->next;
	}
}
