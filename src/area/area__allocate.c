/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area__allocate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:40:41 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:41:06 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

t_block			*area__allocate_new_block(t_area *a, size_t size)
{
	t_block	*b;

	assert(AREA__CAN_FIT(a, size + sizeof(t_block)));
	b = block__allocate((void*)((char*)a + a->cur_size), size);
	a->cur_size += size + sizeof(t_block);
	#ifdef LOG
	block__log(b, "new\t");
	#endif
	return (b);
}

t_block			*area__allocate_free_block(t_area *a, t_free_block *fb)
{
	t_block	*b;
	t_block	*next;

	assert(fb->block.free);
	next = BLOCK__NEXT(&fb->block);
	if (AREA__IS_IN_BOUNDS(a, next))
		block__allocate_prev(next);
	b = free_block__allocate(fb);
	return (b);
}
