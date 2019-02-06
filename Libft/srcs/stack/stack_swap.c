/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:29:25 by theo              #+#    #+#             */
/*   Updated: 2018/11/08 15:40:59 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>

int		stack_swap(t_stack *s)
{
	void	*tmp;

	if (s == NULL || s->next == NULL)
		return (0);
	tmp = s->data;
	s->data = s->next->data;
	s->next->data = tmp;
	return (0);
}
