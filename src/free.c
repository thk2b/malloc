/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:08:36 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/08 06:39:26 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <shared.h>

extern t_free_list	g_free_lists[];
extern t_area_list	g_area_list;

#ifdef LOG

static inline void	free__log(void *ptr)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	put_str(fd, "free(");
	put_hex(fd, (size_t)ptr, 1);
	put_str(fd, ")\n");
}

#endif

extern void			free(void *ptr)
{
	t_area			*a;
	t_block			*b;
	t_free_block	*fb;
	t_free_list		*fl;

#ifdef LOG
	free__log(ptr);
#endif
	if (ptr == NULL)
		return ;
	a = area_list__search(&g_area_list, area__find_in_range, ptr);
	if (a)
		b = area__search(a, block__find_address, ptr);
	if (a == NULL || b == NULL || b->free == 1)
	{
		return ;
	}
	if ((fb = area__deallocate_block(a, b)) == NULL)
		return ;
	fl = free_list__find(g_free_lists, b->size);
	free_list__insert(fl, a, fb);
}
