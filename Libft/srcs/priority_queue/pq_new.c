/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:00:09 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 23:25:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include "libft.h"
#include <stdlib.h>

t_pq	*pq_new(void *data, int value)
{
	t_pq	*pq;

	MCK(pq = (t_pq*)malloc(sizeof(t_pq)), NULL);
	pq->data = data;
	pq->next = NULL;
	pq->value = value;
	return (pq);
}
