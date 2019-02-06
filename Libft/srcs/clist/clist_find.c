/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 00:52:58 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 01:02:14 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clist.h>

void	*clist_find(t_clist *cl, void *ctx, t_clist_cmp_fn cmp)
{
	t_clist	*cur;

	if (cl == NULL)
		return (NULL);
	cur = cl;
	while (1)
	{
		if (cmp(ctx, cur->data))
			return (cur->data);
		cur = cur->next;
		if (cur == cl)
			break ;
	}
	return (NULL);
}
