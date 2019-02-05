/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area__deallocate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:42:03 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:42:29 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

extern t_free_list	g_free_lists[];
extern t_area_list	g_area_list;

t_free_block	*area__deallocate_block(t_area *a, t_block *b)
{
	t_free_block	*fb;
	t_block			*next;

	assert(b->free == 0);
	next = BLOCK__NEXT(b);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__deallocate_prev(next);
	if (a->is_single_block)
	{
		area_list__remove(&g_area_list, a);
		return (NULL);
	}
	if (AREA__CUR_END(a) == (void*)BLOCK__NEXT(b))
	{
		area__deallocate_wilderness_block(a, b);
		return (NULL);
	}
	fb = free_block__deallocate(b);
	return (fb);
}

void			area__destroy_free_block(t_area *a, t_free_block *fb)
{
	t_free_list	*fl;
	t_block		*next;

	assert(fb->block.free);
	#ifdef LOG
	free_block__log(fb, "destroy");
	#endif
	fl = free_list__find(g_free_lists, fb->block.size);
	free_list__remove(fl, a, fb);
	next = BLOCK__NEXT(&fb->block);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__allocate_prev(next);
}

void			area__destroy_block(t_area *a, t_block *b)
{
	assert(AREA__CUR_END(a) == (void*)BLOCK__NEXT(b));
	assert(a->cur_size >= b->size + sizeof(t_block));
	a->cur_size -= b->size + sizeof(t_block);
	assert(a->cur_size >= sizeof(t_area));
}
