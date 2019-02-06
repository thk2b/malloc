/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:26:26 by theo              #+#    #+#             */
/*   Updated: 2018/11/08 15:28:59 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>

void	*stack_pop(t_stack **s)
{
	t_stack *top;
	void	*ret;

	if (*s == NULL)
		return (NULL);
	top = *s;
	*s = top->next;
	ret = top->data;
	free(top);
	return (ret);
}
