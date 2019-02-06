/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:46:13 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 18:28:50 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

static void	next(t_llist_node *nodes[3])
{
	nodes[0] = nodes[1];
	nodes[1] = nodes[1]->next;
}

int			llist_remove(t_llist *head, void *ctx,
	t_llist_cmp_fn cmp, t_llist_del_fn del)
{
	t_llist_node	*nodes[3];

	nodes[0] = NULL;
	nodes[1] = head->first;
	while (nodes[1])
	{
		nodes[2] = nodes[1]->next;
		if (cmp(ctx, nodes[1]->data))
		{
			if (nodes[0] == NULL)
				head->first = nodes[2];
			else if (nodes[1] == head->last)
				head->last = nodes[0];
			else
				nodes[0]->next = nodes[2];
			del(nodes[1]);
			head->len--;
			return (0);
		}
		else
			next(nodes);
	}
	return (1);
}
