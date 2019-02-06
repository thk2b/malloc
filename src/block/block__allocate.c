/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block__allocate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 06:52:46 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 06:52:58 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

t_block	*block__allocate(void *addr, size_t size)
{
	t_block	*b;

	b = (t_block*)addr;
	b->prev_free = 0;
	b->free = 0;
	b->size = size;
	return (b);
}

void	block__deallocate_prev(t_block *b)
{
	b->prev_free = 1;
}

void	block__allocate_prev(t_block *b)
{
	b->prev_free = 0;
}
