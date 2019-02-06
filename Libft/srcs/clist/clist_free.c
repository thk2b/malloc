/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 22:38:08 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/11 23:40:45 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clist.h>

void	clist_free(t_clist *cl, t_clist_del_fn del)
{
	t_clist	*cur;
	t_clist	*next;

	if (cl == NULL)
		return ;
	if (del == NULL)
		del = free;
	cur = cl;
	cl->prev->next = NULL;
	while (cur)
	{
		del(cur->data);
		next = cur->next;
		free(cur);
		cur = next;
	}
}
