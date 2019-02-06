/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:22:44 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 00:49:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "libft.h"
#include <stdlib.h>

t_llist			*llist_new(void)
{
	t_llist	*head;

	MCK(head = (t_llist*)malloc(sizeof(t_llist)), NULL);
	head->first = NULL;
	head->last = NULL;
	head->len = 0;
	return (head);
}

t_llist_node	*llist_new_node(void *data)
{
	t_llist_node *node;

	MCK(node = (t_llist_node*)malloc(sizeof(t_llist_node)), NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
