/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_new_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:18:23 by theo              #+#    #+#             */
/*   Updated: 2018/11/08 16:28:59 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>
#include <libft.h>

t_stack		*stack_new_node(void *data)
{
	t_stack	*s;

	MCK(s = (t_stack*)malloc(sizeof(t_stack)), NULL);
	s->data = data;
	s->next = NULL;
	return (s);
}
