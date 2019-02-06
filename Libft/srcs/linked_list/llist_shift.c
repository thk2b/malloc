/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:38:20 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 00:49:17 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"

int		llist_shift(t_llist **head, void *data)
{
	t_llist_node	*node;

	MCK(node = llist_new_node(data), 1);
	if (*head == NULL)
	{
		MCK(*head = llist_new(), 1);
		(*head)->first = node;
	}
	else
		node->next = (*head)->first;
	(*head)->first = node;
	(*head)->len++;
	return (0);
}
