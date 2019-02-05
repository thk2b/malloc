/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area__find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:43:06 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:44:46 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

int		area__find_in_range(t_area *a, void *ctx)
{
	return (AREA__IS_IN_BOUNDS(a, ctx));
}

int		area__find_has_free_block(t_area *a, void *ctx)
{
	return (AREA__HAS_FREE_BLOCK(a, *(size_t*)ctx));
}

void	area__foreach(t_area *a, t_area__foreach_fn fn, void *ctx)
{
	t_block	*b;
	void	*end;
	size_t	index;

	index = 0;
	end = AREA__CUR_END(a);
	b = AREA__HEAD(a);
	while ((void*)b < end)
	{
		fn(b, index++, ctx);
		b = BLOCK__NEXT(b);
	}
}

t_block	*area__search(t_area *a, t_area__search_fn fn, void *ctx)
{
	t_block	*b;
	void	*end;

	end = AREA__CUR_END(a);
	b = AREA__HEAD(a);
	while ((void*)b < end)
	{
		if (fn(b, ctx))
			return (b);
		b = BLOCK__NEXT(b);
	}
	return (NULL);
}
