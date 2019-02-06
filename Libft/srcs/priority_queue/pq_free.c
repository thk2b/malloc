/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:04:12 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/24 13:27:56 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include <stdlib.h>

static void	default_del(void *data)
{
	free(data);
}

void		pq_free(t_pq *pq, t_pq_del_fn del)
{
	t_pq	*cur;
	t_pq	*next;

	cur = pq;
	if (del == NULL)
		del = default_del;
	while (cur)
	{
		next = cur->next;
		del(cur->data);
		free(cur);
		cur = next;
	}
}
