/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:33:24 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/06 07:42:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

static inline void	dumb(unsigned char *d, size_t i)
{
	#ifndef HEXDUMP_BG
	put_str(1, HEXDUMP_ADDRESS);
	put_hex(1, (size_t)(d + i), 0);
	put_str(1, " ");
	put_str(1, RESET);
	#endif
}

static inline void	dump(unsigned char *d, size_t i)
{
	unsigned char	n;

	n = d[i];
	i += 1;
	put_hex(1, (size_t)n, 0);
	if (n < 16)
		put_str(1, "0");
	put_str(1, " ");
}

void				hexdump(void *ptr, size_t size, char *color)
{
	static size_t	count = 0;
	size_t			i;
	unsigned char	*d;

	if (ptr == NULL)
	{
		count = 0;
		return ;
	}
	i = 0;
	d = (unsigned char*)ptr;
	while (i < size)
	{
		if (count == 0)
			dumb(d, i);
		put_str(1, color);
		while (i < size && count++ < HEXDUMP_WIDTH)
			dump(d, i++);
		if (i >= size)
			break ;
		count = 0;
		put_str(1, RESET "\n");
	}
	put_str(1, RESET);
}
