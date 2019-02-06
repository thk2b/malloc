/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:06:10 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/24 11:45:42 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include "libft.h"
#include <stdlib.h>

int	pq_add(t_pq **pq, void *data, int value, t_pq_sort sort_type)
{
	t_pq	*el;
	t_pq	*cur;
	t_pq	*prev;

	MCK(el = pq_new(data, value), 1);
	if (*pq == NULL)
		return (!((*pq = el)));
	prev = NULL;
	cur = *pq;
	while (cur && PQ_CMP(sort_type, cur->value, value))
	{
		prev = cur;
		cur = cur->next;
	}
	if (prev)
		prev->next = el;
	el->next = cur;
	if (cur == *pq)
		*pq = el;
	return (0);
}
