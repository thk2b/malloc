/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list__find_first_fit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:19:12 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:19:12 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

int		free_list__find_first_fit(t_area *a, t_free_block *fb, void *ctx)
{
	size_t	size;

	UNUSED(a);
	assert(fb->block.free);
	size = *(size_t*)ctx;
	return (fb->block.size >= size);
}
