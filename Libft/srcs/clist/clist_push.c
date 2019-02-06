/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 22:59:16 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 00:35:12 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clist.h>

int		clist_push(t_clist **cl, void *data)
{
	t_clist *n;

	MCK(n = clist_new(data), 1);
	if (*cl == NULL)
	{
		n->next = n;
		n->prev = n;
	}
	else
	{
		n->next = (*cl);
		n->prev = (*cl)->prev;
		(*cl)->prev->next = n;
		(*cl)->prev = n;
	}
	*cl = n;
	return (0);
}
