/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:01:28 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:05:13 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <shared.h>

t_free_list			*free_list__find(t_free_list *fls, size_t size)
{
	size_t		i;

	i = 1;
	while (i < FL__N_FREE_LISTS && fls[i].min_size <= size)
	{
		i++;
	}
	return (fls + (i - 1));
}

void				free_list__insert(t_free_list *fl,
	t_area *a, t_free_block *fb)
{
	free_list__insert_local_address_ordered(fl, a, fb);
}

void				free_list__remove(t_free_list *fl,
	t_area *area, t_free_block *fb)
{
	t_free_block	*prev;
	t_free_block	*next;

	if (fb->block.free == 0)
		return ;
	if (fb == area->first_free_block[fl->id])
		area->first_free_block[fl->id] =
			AREA__IS_IN_BOUNDS(area, fb->next) ? fb->next : NULL;
	if (fb == area->last_free_block[fl->id])
		area->last_free_block[fl->id] =
			AREA__IS_IN_BOUNDS(area, fb->prev) ? fb->prev : NULL;
	prev = fb->prev;
	next = fb->next;
	if (prev == NULL)
		fl->head = next;
	else
		prev->next = next;
	if (next)
		next->prev = prev;
	fb->next = NULL;
	fb->prev = NULL;
}
