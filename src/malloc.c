/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:13:43 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/08 06:39:45 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <shared.h>
#include <assert.h>

extern t_free_list	g_free_lists[];
extern t_area_list	g_area_list;

#ifdef LOG

static inline void	malloc__log(size_t size)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	put_str(fd, "malloc(");
	put_dec(fd, size);
	put_str(fd, ")\n");
}

#endif

extern void			*malloc(size_t size)
{
	t_free_list		*fl;
	t_free_block	*fb;
	t_area			*a;
	t_block			*b;

	size = MAX(ALLIGN(size, 8), FREE_BLOCK__MIN_SIZE);
#ifdef LOG
	malloc__log(size);
#endif
	fl = free_list__find(g_free_lists, size);
	fb = free_list__dynamic_search(
		fl, &a, free_list__find_first_fit_coalesce, (void*)&size);
	if (fb)
	{
		if (fb->block.size > size && area__split_free_block(a, fb, size))
			;
		else
			free_list__remove(
				free_list__find(g_free_lists, fb->block.size), a, fb);
		b = area__allocate_free_block(a, fb);
	}
	else if ((a = area_list__request_mem(&g_area_list, size)))
		b = area__allocate_new_block(a, size);
	return (a ? BLOCK__DATA(b) : NULL);
}
