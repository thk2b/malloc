/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:38:17 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:44:52 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <assert.h>

int				area__can_fit(t_area *a, size_t size)
{
	assert(a->size > a->cur_size);
	return (a->size - a->cur_size > size);
}

void			area__extend(t_area *a, size_t extention_size)
{
	assert(a->is_single_block == 0);
	a->size += extention_size;
	#ifdef LOG
	area__log(a, "extended");
	#endif
}

void			area__hexdump(t_area *a, size_t index, void *ctx)
{
	UNUSED(index);
	UNUSED(ctx);
	hexdump((void*)a, sizeof(t_area), AREA__HEADER_COLOR);
	area__foreach(a, block__hexdump, NULL);
	hexdump((void*)AREA__CUR_END(a),
		AREA__AVAILABLE_SIZE(a), AREA__REMAINING_COLOR);
	put_str(1, a->next ? "\n    ⋮\n" : "\n");
}

void			area__show_alloc(t_area *area, size_t index, void *ctx)
{
	*(size_t*)ctx += area->size;
	put_str(1, "Area ");
	put_dec(1, index);
	put_str(1, "\n");
	area__foreach(area, block__show_alloc, NULL);
	put_dec(1, area->cur_size);
	put_str(1, "/");
	put_dec(1, area->size);
	put_str(1, " bytes\n");
}

#ifdef LOG

void			area__log(t_area *a, char *msg)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	log__line_count(fd);
	put_str(fd, msg);
	put_str(fd, "\t");
	put_str(fd, "area\t\t");
	put_hex(fd, (size_t)a, 1);
	put_str(fd, "\t");
	put_dec(fd, a->size);
	put_str(fd, "\n");
}

#endif
