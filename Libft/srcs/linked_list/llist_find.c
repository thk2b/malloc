/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:43:56 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 20:36:37 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_llist_node	*llist_find(t_llist *head, void *ctx, t_llist_cmp_fn cmp)
{
	t_llist_node	*node;

	if (head == NULL)
		return (NULL);
	node = head->first;
	while (node)
		if (cmp(ctx, node->data))
			return (node);
		else
			node = node->next;
	return (NULL);
}
