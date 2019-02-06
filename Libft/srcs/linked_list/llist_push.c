/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:27:52 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/27 19:55:54 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"

int		llist_push(t_llist **head, void *data)
{
	t_llist_node	*node;

	MCK(node = llist_new_node(data), 1);
	if (*head == NULL)
	{
		MCK(*head = llist_new(), 1);
		(*head)->first = node;
	}
	else
		(*head)->last->next = node;
	(*head)->last = node;
	(*head)->len++;
	return (0);
}
