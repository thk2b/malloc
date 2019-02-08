/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_list__remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 07:23:50 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/08 06:34:13 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <sys/mman.h>

void		area_list__remove(t_area_list *al, t_area *a)
{
	if (al->head == a)
		al->head = a->next;
	if (a->prev)
		a->prev->next = a->next;
	if (a->next)
		a->next->prev = a->prev;
	a->next = NULL;
	a->prev = NULL;
#ifdef LOG
	area__log(a, "remove");
#endif
	munmap((void*)a, a->size);
}
