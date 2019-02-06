/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:37:34 by theo              #+#    #+#             */
/*   Updated: 2018/11/08 17:37:52 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>

/*
**	first element becomes the last
*/

int		stack_rotate(t_stack **s)
{
	t_stack	*top;
	t_stack	*bottom;

	if (*s == NULL || (*s)->next == NULL)
		return (0);
	top = *s;
	bottom = top;
	while (bottom->next)
	{
		bottom = bottom->next;
	}
	bottom->next = top;
	*s = top->next;
	top->next = NULL;
	return (0);
}
