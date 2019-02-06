/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:23:25 by theo              #+#    #+#             */
/*   Updated: 2018/11/08 15:46:26 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>
#include <libft.h>

int		stack_push(t_stack **s, void *data)
{
	t_stack	*n;

	MCK(n = stack_new_node(data), 1);
	if (*s)
		n->next = *s;
	*s = n;
	return (0);
}
