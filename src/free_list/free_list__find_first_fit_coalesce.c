/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list__find_first_fit_coalesce.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:15:46 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:15:57 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

int		free_list__find_first_fit_coalesce(t_area *a,
	t_free_block *fb, t_free_block **next, void *ctx)
{
	size_t			requested_size;
	t_free_block	*new_fb;
	t_free_block	*last_encountered_adjacent_fb;

	requested_size = *(size_t*)ctx;
	if (fb->block.size >= requested_size)
		return (1);
	last_encountered_adjacent_fb = NULL;
	new_fb = area__coalesce_free_block(a, fb,
		requested_size + sizeof(t_block), &last_encountered_adjacent_fb);
	if (new_fb == NULL)
	{
		assert(last_encountered_adjacent_fb == NULL
			|| last_encountered_adjacent_fb > fb);
		*next = last_encountered_adjacent_fb;
		return (0);
	}
	*next = new_fb;
	return (1);
}
