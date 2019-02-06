/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rrotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:14:00 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/08 16:28:14 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>

int		stack_rrotate(t_stack **s)
{
	t_stack	*top;
	t_stack	*bottom;
	t_stack	*bottom_prev;

	if (*s == NULL || (*s)->next == NULL)
		return (0);
	top = *s;
	bottom = top;
	while (bottom->next)
	{
		bottom_prev = bottom;
		bottom = bottom->next;
	}
	bottom_prev->next = NULL;
	bottom->next = top;
	*s = bottom;
	return (0);
}
