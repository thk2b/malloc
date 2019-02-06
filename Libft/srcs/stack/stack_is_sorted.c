/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_is_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:19:38 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/12 01:25:32 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>

/*
**	return 1 if all elements are smaller than the next.
*/

int		stack_is_sorted(t_stack *s, t_stack_cmp_fn cmp)
{
	t_stack	*cur;

	if (s == NULL || s->next == NULL)
		return (1);
	cur = s;
	while (cur->next)
	{
		if (cmp(cur->data, cur->next->data) > 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}
