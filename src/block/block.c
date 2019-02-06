/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 06:51:01 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 06:56:00 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

int		block__find_address(t_block *b, void *ctx)
{
	return (BLOCK__DATA(b) == ctx);
}

void	block__show_alloc(t_block *block, size_t index, void *ctx)
{
	UNUSED(index);
	UNUSED(ctx);
	put_str(1, "\tBlock\t");
	put_dec(1, index);
	put_str(1, "\t");
	put_hex(1, (size_t)BLOCK__DATA(block), 1);
	put_str(1, block->free ? "\tF\t" : "\tU\t");
	put_dec(1, block->size);
	put_str(1, " bytes\n");
}

void	block__hexdump(t_block *b, size_t index, void *ctx)
{
	if (b->free)
	{
		free_block__hexdump((t_free_block*)b, index, ctx);
		return ;
	}
	hexdump((void*)b, sizeof(t_block), BLOCK__HEADER_COLOR);
	hexdump(BLOCK__DATA(b), b->size, BLOCK__DATA_COLOR);
}

#ifdef LOG

void	block__log(t_block *b, char *msg)
{
	int fd;

	if ((fd = log__get_fd()) < 0)
		return ;
	log__line_count(fd);
	put_str(fd, msg);
	put_str(fd, "\tblock\t\t");
	put_hex(fd, (size_t)b, 1);
	put_str(fd, "\t");
	put_dec(fd, b->size);
	put_str(fd, "\n");
}

#endif
