/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 22:54:07 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/11 23:28:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <clist.h>

t_clist		*clist_new(void *data)
{
	t_clist	*cl;

	MCK(cl = (t_clist*)malloc(sizeof(t_clist)), NULL);
	cl->next = NULL;
	cl->prev = NULL;
	cl->data = data;
	return (cl);
}
