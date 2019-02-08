/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area__split_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:53:38 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/08 06:35:55 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

extern t_free_list	g_free_lists[];

/*
**	Resize b to target size and create a new free block with the remainder
**	target size must be 8 byte alligned and smaller than the block
**	Teh entire block is removed from the free list
**	The first part of the free block is not added to a free list.
**	The remainder is added to a free list
**	Return 1 if the block was split, 0 otherwise
*/

int					area__split_block(t_area *a, t_block *b, size_t target_size)
{
	size_t			new_block_size;
	t_block			*new_block;
	t_free_block	*new_free_block;
	t_free_list		*fl;

	assert(b->size >= target_size);
	new_block_size = b->size - target_size - sizeof(t_block);
	if (new_block_size < FREE_BLOCK__MIN_SIZE)
		return (0);
	b->size = target_size;
#ifdef LOG
	block__log(b, "split");
#endif
	new_block = BLOCK__NEXT(b);
	new_block->size = new_block_size;
	new_block->prev_free = 0;
	new_block->free = 0;
	new_free_block = area__deallocate_block(a, new_block);
	assert(new_free_block->block.free);
	fl = free_list__find(g_free_lists, new_block_size);
	free_list__insert(fl, a, new_free_block);
	return (1);
}
