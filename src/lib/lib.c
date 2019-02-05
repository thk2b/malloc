/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 07:35:19 by tkobb             #+#    #+#             */
/*   Updated: 2019/02/05 07:35:20 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

void	put_hex(int fd, size_t n, int prefix)
{
	char		buf[67];
	static char	sym[] = "0123456789abcdef";
	size_t		n_div;
	size_t		div;
	size_t		i;

	ft_bzero(buf, 67);
	if (prefix)
	{
		buf[0] = '0';
		buf[1] = 'x';
	}
	div = 1;
	while ((n_div = div * 16) <= n && n_div > div)
		div = n_div;
	i = prefix ? 2 : 0;
	while (div)
	{
		buf[i++] = sym[n / div % 16];
		div /= 16;
	}
	write(fd, buf, i);
}

void	put_dec(int fd, size_t n)
{
	char		buf[64];
	static char	sym[] = "0123456789";
	size_t		n_div;
	size_t		div;
	size_t		i;

	ft_bzero(buf, 64);
	div = 1;
	while ((n_div = div * 10) <= n && n_div > div)
		div = n_div;
	i = 0;
	while (div)
	{
		buf[i++] = sym[n / div % 10];
		div /= 10;
	}
	write(fd, buf, i);
}

void	put_str(int fd, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}
