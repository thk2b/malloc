/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:24:35 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/25 15:40:07 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include <stdlib.h>

void	*llist_free(t_llist *head, t_llist_del_fn del)
{
	t_llist_node	*node;
	t_llist_node	*next;

	node = head->first;
	while (node)
	{
		next = node->next;
		del(node->data);
		free(node);
		node = next;
	}
	free(head);
	return (NULL);
}
