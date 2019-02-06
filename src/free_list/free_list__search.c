/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list__search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:04:34 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:14:24 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

extern t_area_list			g_area_list;

/*
**	Iterates through the free list
**	Return the first free block for which fn returns 1
**	Sets areap to the area in which the block is found.
*/

static inline t_free_block	*dumb(t_area **areap,
	t_area *area, t_free_block *cur)
{
	*areap = area;
	return (cur);
}

t_free_block				*free_list__search(t_free_list *fl,
	t_area **areap, t_free_list__search_fn fn, void *ctx)
{
	t_area			*area;
	t_free_block	*cur;
	void			*area_end;

	cur = fl->head;
	if (cur == NULL)
		return (NULL);
	area = area_list__search(&g_area_list, area__find_in_range, (void*)cur);
	while (cur)
	{
		if (!AREA__IS_IN_BOUNDS(area, cur))
		{
			area = area_list__search_from(
				area, area__find_in_range, (void*)cur);
			assert(area);
			area_end = AREA__CUR_END(area);
		}
		if (fn(area, cur, ctx))
			return (dumb(areap, area, cur));
		cur = cur->next;
	}
	*areap = NULL;
	return (NULL);
}

/*
**	Iterates through the free list
**	Return the first free block for which fn returns 1
**	If next is not NULL, continue the search from there
**	Sets areap to the area in which the block is found.
*/

static inline t_free_block	*dumber(t_area **areap,
	t_area *area, t_free_block *next, t_free_block *cur)
{
	*areap = area;
	return (next ? next : cur);
}

t_free_block				*free_list__dynamic_search(t_free_list *fl,
	t_area **areap, t_free_list__dynamic_search_fn fn, void *ctx)
{
	t_area			*area;
	t_free_block	*cur;
	t_free_block	*next;
	void			*area_end;

	cur = fl->head;
	if (cur == NULL)
		return (NULL);
	area = area_list__search(&g_area_list, area__find_in_range, (void*)cur);
	while (cur)
	{
		if (!AREA__IS_IN_BOUNDS(area, cur))
		{
			area = area_list__search_from(
				area, area__find_in_range, (void*)cur);
			area_end = AREA__CUR_END(area);
		}
		next = NULL;
		if (fn(area, cur, &next, ctx))
			return (dumber(areap, area, next, cur));
		cur = next ? next : cur->next;
	}
	*areap = NULL;
	return (NULL);
}

t_free_block				*free_list__search_in_area(
	t_free_list *fl, t_area *a, t_free_list__search_fn fn, void *ctx)
{
	t_free_block	*b;
	t_free_block	*last;

	b = a->first_free_block[fl->id];
	last = a->last_free_block[fl->id];
	while (b && b <= last)
	{
		if (fn(a, b, ctx))
			return (b);
		b = b->next;
	}
	return (NULL);
}
