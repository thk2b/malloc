/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_is_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 22:44:06 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 01:00:03 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clist.h>

/*
**	return 1 if all elements are inferior to the next.
*/

int		clist_is_sorted(t_clist *cl, t_clist_cmp_fn cmp)
{
	t_clist	*cur;

	if (cl == NULL)
		return (1);
	cur = cl;
	while (cur->next != cl)
	{
		if (cmp(cur->data, cur->next->data) == 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}
