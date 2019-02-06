/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 18:49:23 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:51:58 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIORITY_QUEUE_H
# define PRIORITY_QUEUE_H
# include "linked_list.h"

# define PQ_CMP(sort, a, b) ((sort) == PQS_DESC ? (a) >= (b) : (a) <= (b))

typedef struct	s_pq
{
	int			value;
	void		*data;
	struct s_pq	*next;
}				t_pq;

typedef void	(*t_pq_del_fn)(void *data);

typedef enum	e_pq_sort
{	PQS_DESC,
	PQS_ASC
}				t_pq_sort;

t_pq			*pq_new(void *data, int value);
void			pq_free(t_pq *pq, t_pq_del_fn del);
int				pq_add(t_pq **pq, void *data, int value, t_pq_sort sort_type);
void			*pq_get(t_pq *pq);
void			*pq_pop(t_pq **pq);

#endif
